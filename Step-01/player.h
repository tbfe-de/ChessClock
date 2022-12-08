#ifndef PLAYER_H_
#define PLAYER_H_

#include <atomic>

enum player : std::size_t {
    NONE = 0,   // !!! do not change any of these values
    WHITE = 1,  // !!! as they will be used to index the
    BLACK = 2   // !!! `player_clock` array (see below)
};
extern std::atomic<player> active;

#endif // include guard
