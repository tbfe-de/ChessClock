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
#include <iomanip>
#include <iostream>
#include <iosfwd>
#include <string>

class PlayerClock {
    using value_type = std::uint_least16_t;;
public:
    // construction and destruction:
    PlayerClock(std::string const& name, value_type count)
        : name_{name}, count_{count}
    {}
    PlayerClock(PlayerClock const&)             =default;
//  PlayerClock& operator=(PlayerClock const&) // implemented below
    PlayerClock(PlayerClock&&)                  =default;
    PlayerClock& operator=(PlayerClock&&)       =default;
    ~PlayerClock()                              =default;

    // queries:
    auto get_name() const { return name_; }
    auto expired() const { return (count_ == 0); }
    operator value_type() const { return count_; }
    explicit operator bool() const { return (count_ > 0); }

    // modifiers:
    PlayerClock& operator=(PlayerClock const& rhs) {
        count_ = rhs.count_; return *this;
    }
    PlayerClock& operator=(value_type rhs) {
        count_ = rhs; return *this;
    }
    PlayerClock& operator--() {     // `--` as prefix operator
        --count_; return *this;
    }
    PlayerClock operator--(int) {   // `--` as postfix operator
        PlayerClock result = *this; --count_; return result;
    }

private:
    std::string name_{};
    value_type count_{};
    PlayerClock() = default;
    friend class PlayerClock_Array;
};

class PlayerClock_Array {
public:
    PlayerClock_Array();
    void set();
    PlayerClock& operator[](Player idx) {
        return clk_array[idx];
    }
    PlayerClock const& operator[](Player idx) const {
        return clk_array[idx];
    }

private:
    PlayerClock clk_array[3];
    static_assert((sizeof clk_array / sizeof clk_array[0]) == 3,
                    "maybe incompatible change to `enum player`");

};

extern std::ostream& operator<<(std::ostream &, PlayerClock const&);

extern PlayerClock_Array pclk;

#endif // include guard
