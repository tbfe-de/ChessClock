/* C++ module implementation
 ===============================================================================
 Chess Clock Main Program
 ===============================================================================
 ...
*/

// own header file always goes first
#include "utils.h"

// project specific header files (alphabetically sorted)
// ==NONE==

// standard library header files (alphabetically sorted)
#include <regex>

int parse_mins_secs(std::string const& str, int preset) {
    std::istringstream is{str};
    int minutes = preset/60;
    int seconds = preset%60;
    std::string s;
    std::regex re{R"([ \t]*([0-9]*):([0-9]*)[ \t]*)"};
    std::smatch m;
    if (std::regex_match(str, m, re)) {
        if (!m[1].str().empty() && !m[2].str().empty()) {
            minutes = std::stoi(m[1].str());
            seconds = std::stoi(m[2].str());
        }
        else if (!m[1].str().empty()) {
            minutes = std::stoi(m[1].str());
            seconds = 0;
        }
        else if (!m[2].str().empty()) {
            minutes = 0;
            seconds = std::stoi(m[2].str());
        }
    }
    return 60*minutes + seconds;
}
