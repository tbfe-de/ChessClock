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
#include <iostream>
#include <sstream>

int parse_mins_secs(std::string const& str, int preset) {
    std::istringstream is{str};
    int minutes = preset/60;
    int seconds = preset%60;
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
    return 60*minutes + seconds;
}
