/* C++ header file
 ===============================================================================
 Chess Clock Command Line Menu
 ===============================================================================
 ...
*/

#ifndef CLI_MENU_H_
#define CLI_MENU_H_

// project specific header files (alphabetically sorted)
// ==NONE==

// standard library header files (alphabetically sorted)
#include <functional>
#include <initializer_list>
#include <string>

using menu_prompt = std::string;
using menu_action = std::function<bool(std::string const&)>;

struct menu_control {
    menu_prompt prompt;
    menu_action action;
};

extern bool menu(std::initializer_list<menu_control>);
extern bool quit(std::string const&);

#endif // include guard
