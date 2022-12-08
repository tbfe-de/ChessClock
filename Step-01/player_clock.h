#ifndef PLAYER_CLOCK_H_
#define PLAYER_CLOCK_H_

#include "player.h"

#include <cstdint>
#include <ostream>

struct player_clock {
    char const* const name;
    std::uint_least16_t count;
};

extern player_clock pclk[];
extern void set_clocks();

std::ostream& show_single_clock(std::ostream &, player);

#endif // include guard
