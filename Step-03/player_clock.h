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
#include <string>

class PlayerClock {
    using name_type = std::string;
    using value_type = std::uint_least16_t;
public:
    PlayerClock(name_type const name, value_type count)
        : name_{name}, count_{count}
    {}
    auto get_count() const { return count_; }
    auto set_count(value_type count) { count_ = count; }
    auto decrement() { --count_; }
    auto get_name() const { return name_; }
private:
    name_type const name_;
    std::uint_least16_t count_;
};

extern PlayerClock pclk[];
extern void set_clocks();

std::ostream& operator<<(std::ostream&, const PlayerClock&);

#endif // include guard
