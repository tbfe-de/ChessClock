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
#include <cstring>
#include <memory>
#include <iosfwd>
#include <string>

class PlayerClock {
    using value_type = std::uint_least16_t;
public:
    // construction and destruction:
    PlayerClock(std::string const& name, value_type count)
        : name_{name}, count_{count}
    {}
    PlayerClock()                               =delete;
    PlayerClock(PlayerClock const&)             =default;
//  PlayerClock& operator=(PlayerClock const&) // see alias below
    PlayerClock(PlayerClock&&)                  =default;
    PlayerClock& operator=(PlayerClock&&)       =default;
    ~PlayerClock()                              =default;

    // queries:
    auto get_count() const { return count_; }
    auto get_name() const { return name_; }
    // aliases:
    operator value_type() const { return get_count(); }

    // modifiers:
    void set_count(value_type count) { count_ = count; }
    void decrement() { --count_; }
    // aliases:
    PlayerClock& operator=(PlayerClock const& rhs) {
        set_count(rhs.get_count()); return *this;
    }
    PlayerClock& operator=(value_type rhs) {
        set_count(rhs); return *this;
    }
    PlayerClock& operator--() {     // `--` as prefix operator
        decrement(); return *this;
    }
    PlayerClock operator--(int) {   // `--` as postfix operator
        PlayerClock result = *this; decrement(); return result;
    }

private:
    std::string const name_;
    value_type count_;
};

extern PlayerClock pclk[];
extern void set_clocks();

std::ostream& operator<<(std::ostream&, const PlayerClock&);

#endif // include guard
