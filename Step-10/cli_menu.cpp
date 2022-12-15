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
#include "player.h"
#include "ticker_thread.h"

// standard library header files (alphabetically sorted)
#include <iostream>
#include <regex>

bool menu(std::initializer_list<menu_control> ctl) {
    using namespace std;
    auto remap_keysym = [](std::string const &cl) {
        if (cl.empty()) return cl;
        switch (cl.at(0)) {
            case '_':
                return "\u23CE" + cl.substr(1);
                // UTF-8 :^^^^: CR key symbol
            default:
                return cl;
        }
    };
    auto show_prompts = [&](){
        for (auto const &e : ctl) {
            cout << remap_keysym(e.prompt) << '\n';
        }
        show_clocks(1<<Player::NONE);
    };
    auto normalize_input = [](std::string s) {
        {   // trim left white space
            std::regex re{"^[\t ]*"};
            s = regex_replace(s, re, "");
        }
        {   // trim right white space
            std::regex re{"[\t ]*$"};
            s = regex_replace(s, re, "");
        }
        {   // replace empty with underscore
            if (s.empty()) s = "_";
        }
        return s;
    };
    auto find_action = [&](char ch) -> menu_action {
        for (auto const e : ctl) {
            if (ch == e.prompt.at(0))
                return e.action;
        }
        return {};
    };
    show_prompts();

    std::string cmd;
    while (cout << ": ", getline(cin, cmd)) {
        cmd = normalize_input(cmd);
        auto const cmd_char = std::toupper(cmd.at(0));
        if (auto action = find_action(cmd_char)) {
            if (not action(cmd.substr(1))) break;
        }
        else std::cout << "! no such command\n";
    }
    return false;
}

bool quit(std::string const&) {
    return false;
}
