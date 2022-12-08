#ifndef CLI_MENU_H_
#define CLI_MENU_H_

#include <functional>
#include <string>

using menu_prompt = std::string;
using menu_action = std::function<bool(std::string const &)>;

struct menu_control {
    menu_prompt prompt;
    menu_action action;
};

extern bool menu(std::initializer_list<menu_control>);
extern bool quit(std::string const&);

#endif // include guard
