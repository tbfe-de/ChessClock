#include <atomic>
#include <cctype>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <functional>
#include <iomanip>
#include <iostream>
#include <future>
#include <sstream>
#include <string>
#include <thread>

std::ofstream aux_tty; // <-------- should go before ...
std::ostream aux_out{std::cout.rdbuf()}; // ... this one

enum player : std::size_t {
    NONE = 0,   // !!! do not change any of these values
    WHITE = 1,  // !!! as they will be used to index the
    BLACK = 2   // !!! `player_clock` array (see below)
};
std::atomic<player> active = NONE;

using counter_t = std::uint_least32_t;
struct player_clock_t {
    char const* const name;
    std::uint_least16_t count;
} pclk[] = {
    {"START", 15*60},
    {"WHITE", 0},
    {"BLACK", 0}
};
static_assert((sizeof pclk / sizeof pclk[0]) == 3,
              "maybe incompatible change to `enum player` above)");

decltype(auto) show_single_clock(std::ostream &strm,
                                 player_clock_t const& clk) {
    extern char const* ticker_indicator;
    auto const val = clk.count;
    auto const txt = clk.name;
    std::ostream os{strm.rdbuf()};
    os.fill('0');
    os << '\r' << *ticker_indicator
        << ' ' << txt
        << ' ' << std::setw(2) << val/60
        << ':' << std::setw(2) << val%60;
    os.flush();
    return strm;
}

void show_clocks(unsigned which) {
    aux_out << "+ ------------------------------\n";
    if (which & (1<<NONE))
        show_single_clock(aux_out, pclk[NONE])
                            << " preset" << std::endl;
    if (which & (1<<WHITE))
        show_single_clock(aux_out, pclk[WHITE])
                            << " initial" << std::endl;
    if (which & (1<<BLACK))
        show_single_clock(aux_out, pclk[BLACK])
                            << " initial" << std::endl;
}

void set_clocks() {
    pclk[WHITE].count = pclk[NONE].count;
    pclk[BLACK].count = pclk[NONE].count;
}

auto parse_mins_secs(std::string const& str) {
    std::istringstream is{str};
    auto minutes = pclk[NONE].count / 60;
    auto seconds = pclk[NONE].count % 60;
    std::string s;
    int v;
    if (std::getline(is, s, ':')) {
        if (s.empty())
            minutes = 0;
        else {
            std::istringstream is2{s};
            if (is2 >> v) minutes = v;
            else minutes = 0;
            seconds = 0;
        }
        if (std::getline(is, s)) {
            if (!s.empty()) {
                std::istringstream is2{s};
                if (is2 >> v) seconds = v;
                else seconds = 0;
            }
        }
    }
    pclk[NONE].count = 60*minutes + seconds;
}

auto reset(std::string const& str) {
    parse_mins_secs(str);
    set_clocks();
    auto selected = (1<<WHITE) | (1<<BLACK);
    if (!str.empty()) selected |= (1<<NONE);
    show_clocks(selected);
    return true;
}

char const ticker_symbols[] = {
        '|',  '/', '-', '\\',
        '|',  '/', '-', '\\', };
auto const N_TICKER_SYMBOLS = sizeof(ticker_symbols);
static_assert(N_TICKER_SYMBOLS == 8);
char const *ticker_indicator = &ticker_symbols[0];

auto ticker_thread() {
    auto step = std::chrono::steady_clock::now();
    int phase = 0;
    while ((pclk[WHITE].count > 0)
        && (pclk[BLACK].count > 0)) {
        phase = (phase + 1) % N_TICKER_SYMBOLS;
        ticker_indicator = &ticker_symbols[phase];
        if (phase == 0) --pclk[active].count;
        show_single_clock(aux_out, pclk[active]);
        using namespace std::chrono_literals;
        static_assert(1000 % N_TICKER_SYMBOLS == 0,
                      "otherwise clock skew will accumulate");
        step += 1000ms / N_TICKER_SYMBOLS;
        std::this_thread::sleep_until(step);
    }
    switch (active) {
        case WHITE:
            aux_out << "\r| WHITE time expired\n";
            show_single_clock(aux_out, pclk[BLACK]);
            break;
        case BLACK:
            aux_out << "\r| BLACK time expired\n";
            show_single_clock(aux_out, pclk[WHITE]);
            break;
        default:
            break;
    }
    aux_out << " (wins)" << std::endl;
    std::cout << "hit <Return> to continue" << std::flush;
    active = NONE;
}

std::future<void> clockwork;

auto start(std::string const&) {
    if ((pclk[WHITE].count == 0)
     || (pclk[BLACK].count == 0)) {
        std::cout << "! not yet (re-)set to start time\n";
    }
    else {
        active = WHITE;
        clockwork = std::async(ticker_thread);
    }
    return true;
}

auto toggle_player() {
    if (aux_tty) aux_out.put('\n');
    switch (active) {
        case WHITE: active = BLACK; break;
        case BLACK: active = WHITE; break;
    }
}

using menu_prompt = std::string;
using menu_action = std::function<bool(std::string const &)>;

struct menu_control {
    menu_prompt prompt;
    menu_action action;
};

bool menu(std::initializer_list<menu_control> ctl) {
    using namespace std;
    auto show_prompts = [&](){
        for (auto const e : ctl)
            cout << e.prompt << '\n';
        show_clocks(1<<NONE);
    };
    string cmd;
    auto find_action = [&](char ch) -> menu_action {
        for (auto const e : ctl) {
            if (ch == e.prompt.at(0))
                return e.action;
        }
        return {};
    };

    show_prompts();
    while (cout << ": ", getline(cin, cmd)) {
        if (cmd.empty()) {
            if (active != NONE)
                toggle_player();
        }
        else if (active == NONE) {
            if (clockwork.valid()) {
                clockwork.get();
            }
            auto const cmd_char = std::toupper(cmd.at(0));
            if (auto action = find_action(cmd_char)) {
                if (not action(cmd.substr(1))) break;
            }
            else std::cout << "! no such command\n";
        }
    }
    return false;
}

auto quit(std::string const&) {
    return false;
}

int main(int argc, char *argv[]) {
    if (auto aux_name = std::getenv("CHESSCLOCK_AUX_TTY")) {
        aux_tty.open(aux_name);
        if (aux_tty) {
            aux_out.rdbuf(aux_tty.rdbuf());
        }
    }
    if (aux_tty) aux_out.put('\n');
    if (argc > 1) parse_mins_secs(argv[1]);
    std::cout << "* Welcome from the Chess-Clock *" << std::endl;
    do {} while (menu({
        { "R = (re-)set to <mins>:<secs>\n"
          "    or last start value used", reset },
        { "S = start a game (first white)", start },
        { "Q = end program", quit },
    }));
    std::cout << "* The Chess-Clock says Goodbye *" << std::endl;
}
