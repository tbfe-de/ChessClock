#include <cctype>
#include <cstdint>
#include <functional>
#include <iomanip>
#include <iostream>

using counter_t = std::uint_least32_t;

enum player : std::size_t { NONE, WHITE, BLACK };

counter_t clocks[3] = { 15*60, 0, 0 };

char const clockwork_symbols[] = { '|',  '/', '-', '\\' };
char const *clockwork_indicator = &clockwork_symbols[0];

void show_clocks(unsigned which) {
    auto show_single = [](std::string const& txt, counter_t const clk) {
        std::ostream os{std::cout.rdbuf()};
        os.fill('0');
        os << *clockwork_indicator << ' ' << txt
           << std::setw(2) << clk/60 << ':'
           << std::setw(2) << clk%60 << std::endl;
    };
    std::cout << "* ------------------------------\n";
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

player active = NONE;

auto start(std::string const&) {
    active = WHITE;
    show_clocks(1<<active);
    return true;
}

auto toggle_player() {
    switch (active) {
        case WHITE: active = BLACK; break;
        case BLACK: active = WHITE; break;
    }
    show_clocks(1<<active);
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
        else if (auto action = find_action(toupper(cmd.at(0)))) {
            if (not action(cmd)) break;
        }
        else std::cout << "! no such command\n";
    }
    return false;
}

auto quit(std::string const&) {
    return false;
}

int main() {
    using namespace std::string_literals;
    std::cout << "* Welcome from the Chess-Clock *" << std::endl;
    do {} while (menu({
        { "R = (re-)set to start value"s, reset },
        { "S = start a game (first white)"s, start },
        { "Q = end program"s, quit },
    }));
    std::cout << "* The Chess-Clock says Goodbye *" << std::endl;
}
