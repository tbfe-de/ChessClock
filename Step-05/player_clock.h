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
    PlayerClock& operator=(value_type rhs) {
        count_ = rhs; return *this;
    }
    PlayerClock& operator=(PlayerClock const& rhs) {
        count_ = rhs.count_; return *this;
    }
    operator value_type&() { return count_; }
    operator value_type const&() const { return count_; }
    auto get_name() const { return name_; }
private:
    name_type const name_;
    std::uint_least16_t count_;
};

extern PlayerClock pclk[];
extern void set_clocks();

std::ostream& operator<<(std::ostream&, const PlayerClock&);

#endif // include guard
