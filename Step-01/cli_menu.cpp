/* C++ module implementation
 ===============================================================================
 Chess Clock Command Line Menu
 ===============================================================================
 ...
*/

// own header file always goes first
#include "cli_menu.h"

// project specific header files (alphabetically sorted)
#include "chessclock_app.h"

// standard library header files (alphabetically sorted)
#include <initializer_list>
#include <iostream>

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

bool quit(std::string const&) {
    return false;
}
