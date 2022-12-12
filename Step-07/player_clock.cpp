/* C++ module implementation
 ===============================================================================
 Main Program
 ===============================================================================
 ...
*/

// own header file always goes first
#include "player_clock.h"

// project specific header files (alphabetically sorted)
// ==NONE==

// standard library header files (alphabetically sorted)
#include <iostream>
#include <iomanip>

PlayerClock pclk[]= {
    {"START", 15*60},
    {"WHITE", 0},
    {"BLACK", 0}
};
static_assert((sizeof pclk / sizeof pclk[0]) == 3,
              "maybe incompatible change to `enum player`");

void set_clocks() {
    pclk[WHITE] = pclk[BLACK] = pclk[NONE];
}

std::ostream& operator<<(std::ostream &strm, PlayerClock const& clk) {
    extern char const* ticker_indicator;
    std::ostream os{strm.rdbuf()};
    os.fill('0');
    os << '\r' << *ticker_indicator
        << ' ' << clk.get_name()
        << ' ' << std::setw(2) << clk/60
        << ':' << std::setw(2) << clk%60;
    os.flush();
    return strm;
}
