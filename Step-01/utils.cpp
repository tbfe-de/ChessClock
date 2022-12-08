/* C++ module implementation
 ===============================================================================
 Chess Clock Main Program
 ===============================================================================
 ...
*/

// own header file always goes first
#include "utils.h"

// project specific header files (alphabetically sorted)
#include "player.h"
#include "player_clock.h"

// standard library header files (alphabetically sorted)
#include <iostream>
#include <sstream>

void parse_mins_secs(std::string const& str) {
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
