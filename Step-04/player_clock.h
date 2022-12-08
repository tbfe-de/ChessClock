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
#include <iosfwd>
#include <string>

class PlayerClock {
    using name_type = char const*;
    using value_type = std::uint_least16_t;
    static char const* strdup(const char* s) {
        return std::strcpy(new char[strlen(s)+1], s);
    }
public:
    // construction and destruction:
    PlayerClock(name_type const name, value_type count)
        : name_{strdup(name)}, count_{count}
    {}
    ~PlayerClock() { delete[] name_; }
    PlayerClock()                               =delete;
    PlayerClock(PlayerClock const&)             =delete;
    PlayerClock& operator=(PlayerClock const&)  =delete;
    PlayerClock(PlayerClock&& rhs) noexcept     // move c'tor
        : name_{rhs.name_}, count_{rhs.count_} {
        rhs.name_ = nullptr;
    }
    PlayerClock& operator=(PlayerClock&& rhs) { // move-assign
        if (this != &rhs) {
            delete[] name_;
            name_ = rhs.name_;
            rhs.name_ = nullptr;
            count_ = rhs.count_;
        }
        return *this;
    }

    // queries:
    value_type get_count() const { return count_; }
    name_type get_name() const { return name_; }

    // modifiers:
    void set_count(value_type count) { count_ = count; }
    void decrement() { --count_; }

private:
    name_type name_;
    std::uint_least16_t count_;
};

extern PlayerClock pclk[];
extern void set_clocks();

std::ostream& operator<<(std::ostream&, const PlayerClock&);

#endif // include guard
