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

PlayerClock_Array::PlayerClock_Array() {
    clk_array[NONE] = { "START", 60*15 };
    clk_array[WHITE] = { "WHITE", 0 };
    clk_array[BLACK] = { "BLACK", 0 };
}

void PlayerClock_Array::set() {
    clk_array[WHITE] = clk_array[BLACK] = clk_array[NONE];
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

PlayerClock_Array pclk;
