/* C++ header file
 ===============================================================================
 Chess Clock Player
 ===============================================================================
 ...
*/

#ifndef PLAYER_H_
#define PLAYER_H_

// project specific header files (alphabetically sorted)
// ==NONE==

// standard library header files (alphabetically sorted)
#include <atomic>
#include <cstddef>

enum Player : std::size_t {
    NONE = 0,   // !!! do not change any of these values as
    WHITE = 1,  // !!! they will be used to index the array
    BLACK = 2   // !!! `player_clock` (see `player_clock.h`)
};

extern std::atomic<Player> active;

#endif // include guard
