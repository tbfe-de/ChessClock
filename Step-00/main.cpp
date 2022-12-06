#include <cctype>
#include <functional>
#include <iostream>

using menu_prompt = std::string;
using menu_action = std::function<bool(std::string const &)>;

auto set_clocks(std::string const&) {
    // TBD
    return true;
}
auto start_game(std::string const&) {
    // TBD
    return true;
}

auto toggle_player() {
    // TBD
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
    };
    string cmd;
    auto find_action = [&](char ch) -> menu_action {
        for (auto const e : ctl) {
            if (ch == e.prompt.at(0))
                return e.action;
        }
        return {};
    };

    while (cout << "? ", getline(cin, cmd)) {
        if (cmd.empty())
            toggle_player();
        else if (auto action = find_action(toupper(cmd.at(0)))) {
            if (not action(cmd)) break;
        }
        else std::cout << "! no such command\n";
    }
    return false;
}

auto end_program(std::string const&) {
    return false;
}

int main() {
    using namespace std::string_literals;
    std::cout << "* Welcome to the Chess-Clock" << std::endl;
    do {} while (menu({
        { "R = (re-)set to start value"s, set_clocks },
        { "S = start a game (first white)"s, start_game },
        { "Q = end program"s, end_program },
    }));
    std::cout << "* Goodbye says the Chess-Clock" << std::endl;
}
