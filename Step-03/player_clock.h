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
#include <iosfwd>

struct player_clock {
    player_clock(char const *const n, std::uint_least16_t c)
        : name{n}, count{c}
    {}
    auto get_count() const { return count; }
    auto set_count(std::uint_least16_t c) { count = c; }
    auto decrement() { --count; }
    char const* const name;
private:
    std::uint_least16_t count;
};

extern player_clock pclk[];
extern void set_clocks();

std::ostream& operator<<(std::ostream&, const player_clock&);

#endif // include guard
