#include <atomic>
#include <cctype>
#include <chrono>
#include <cstdint>
#include <functional>
#include <iomanip>
#include <iostream>
#include <future>
#include <string>
#include <thread>

using counter_t = std::uint_least32_t;

enum player : std::size_t { NONE, WHITE, BLACK };

std::atomic<player> active = NONE;

counter_t clocks[3] = { 15*60 };

char const clockwork_symbols[] = {
        '|',  '/', '-', '\\',
        '|',  '/', '-', '\\', };
auto const N_CLOCKWORK_SYMBOLS = sizeof(clockwork_symbols);
static_assert(N_CLOCKWORK_SYMBOLS == 8);
char const *clockwork_indicator = &clockwork_symbols[0];

void show_clocks(unsigned which, bool eol = true) {
    auto show_single = [eol](std::string const& txt, counter_t const clk) {
        std::ostream os{std::cout.rdbuf()};
        os.fill('0');
        if (!eol) os << '\r';
        os << *clockwork_indicator << ' ' << txt
           << std::setw(2) << clk/60 << ':'
           << std::setw(2) << clk%60;
        if (eol) os << '\n';
        os.flush();
    };
    if (eol) std::cout << "* ------------------------------\n";
    if (which & (1<<NONE)) show_single("TOTAL ", clocks[NONE]);
    if (which & (1<<WHITE)) show_single("WHITE ", clocks[WHITE]);
    if (which & (1<<BLACK)) show_single("BLACK ", clocks[BLACK]);
}

void set_clocks() {
    clocks[WHITE] = clocks[NONE];
    clocks[BLACK] = clocks[NONE];
}

using menu_prompt = std::string;
using menu_action = std::function<bool(std::string const &)>;

auto reset(std::string const&) {
    set_clocks();
    show_clocks((1<<WHITE)|(1<<BLACK));
    return true;
}

std::future<void> clockwork;

auto start(std::string const&) {
    if ((clocks[WHITE] == 0) || (clocks[BLACK] == 0)) {
        std::cout << "! not yet (re-) set to start time\n";
        return true;
    }
    else active = WHITE;
    clockwork = std::async([]{
        auto step = std::chrono::steady_clock::now();
        int phase = 0;
        while (clocks[WHITE] && clocks[BLACK]) {
            phase = (phase + 1) % N_CLOCKWORK_SYMBOLS;
            clockwork_indicator = &clockwork_symbols[phase];
            if (phase == 0) --clocks[active];
            show_clocks(1<<active, false);
            using namespace std::chrono_literals;
            static_assert(1000 % N_CLOCKWORK_SYMBOLS == 0,
                          "otherwise clock skew will occur");
            step += 1000ms / N_CLOCKWORK_SYMBOLS;
            std::this_thread::sleep_until(step);
        }
        switch (active) {
            case WHITE:
                std::cout << "\n* BLACK won by WHITE time expired\n";
                break;
            case BLACK:
                std::cout << "\n* WHITE won by BLACK time expired\n";
                break;
            default:
                break;
        }
        std::cout << "* Please hit <Return> to continue" << std::flush;
        active = NONE;
    });
    return true;
}

auto toggle_player() {
    switch (active) {
        case WHITE: active = BLACK; break;
        case BLACK: active = WHITE; break;
    }
}

struct menu_ctl {
    menu_prompt prompt;
    menu_action action;
};

bool menu(std::initializer_list<menu_ctl> ctl) {
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
    while (cout << "? ", getline(cin, cmd)) {
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
                if (not action(cmd)) break;
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
    auto t_mins = 0, t_secs = 0;
    switch (argc) {
        case 3:
            t_mins = std::atoi(argv[argc-2]);
            /*fallthrough*/
        case 2:
            t_secs = std::atoi(argv[argc-1]);
            clocks[NONE] = 60*t_mins + t_secs;
    }
    using namespace std::string_literals;
    std::cout << "* Welcome from the Chess-Clock *" << std::endl;
    do {} while (menu({
        { "R = (re-)set to start value"s, reset },
        { "S = start a game (first white)"s, start },
        { "Q = end program"s, quit },
    }));
    std::cout << "* The Chess-Clock says Goodbye *" << std::endl;
}
