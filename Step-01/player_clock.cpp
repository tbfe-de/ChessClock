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

player_clock pclk[] = {
    {"START", 15*60},
    {"WHITE", 0},
    {"BLACK", 0}
};
static_assert((sizeof pclk / sizeof pclk[0]) == 3,
              "maybe incompatible change to `enum player`");

std::ostream& show_single_clock(std::ostream &strm, player idx) {
    extern char const* ticker_indicator;
    auto const val = pclk[idx].count;
    auto const txt = pclk[idx].name;
    std::ostream os{strm.rdbuf()};
    os.fill('0');
    os << '\r' << *ticker_indicator
        << ' ' << txt
        << ' ' << std::setw(2) << val/60
        << ':' << std::setw(2) << val%60;
    os.flush();
    return strm;
}

void set_clocks() {
    pclk[WHITE].count = pclk[NONE].count;
    pclk[BLACK].count = pclk[NONE].count;
}
