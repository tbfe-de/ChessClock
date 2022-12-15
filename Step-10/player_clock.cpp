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
    clk_array[std::size_t(Player::NONE)] = { "START", 60*15 };
    clk_array[std::size_t(Player::WHITE)] = { "WHITE", 0 };
    clk_array[std::size_t(Player::BLACK)] = { "BLACK", 0 };
}

void PlayerClock_Array::set() {
    auto const initial = operator[](Player::NONE);
    operator[](Player::WHITE) = operator[](Player::BLACK) = initial;
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
