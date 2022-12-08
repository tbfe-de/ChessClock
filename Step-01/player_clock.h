/* C++ header file
 ===============================================================================
 Chess Clock Player Clock
 ===============================================================================
 ...
*/

#ifndef PLAYER_CLOCK_H_
#define PLAYER_CLOCK_H_

// project specific header files (alphabetically sorted)
#include "player.h"

// standard library header files (alphabetically sorted)
#include <cstdint>
#include <ostream>

struct player_clock {
    char const* const name;
    std::uint_least16_t count;
};

extern player_clock pclk[];
extern void set_clocks();

std::ostream& operator<<(std::ostream&, const player_clock&);

#endif // include guard
