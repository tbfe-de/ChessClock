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
    using name_type = char const*;
    using name_holder = std::unique_ptr<char const[]>;
    using value_type = std::uint_least16_t;
    static name_type strdup(const char* s) {
        auto const len = std::strlen(s);
        return std::strcpy(new char[len+1], s);
    }
public:
    // construction and destruction:
    PlayerClock(name_type const name, value_type count)
        : name_{strdup(name)}, count_{count}
    {}
    PlayerClock()                               =delete;
    PlayerClock(PlayerClock const&)             =delete;
    PlayerClock& operator=(PlayerClock const&)  =delete;
    PlayerClock(PlayerClock&&)                  =default;
    PlayerClock& operator=(PlayerClock&&)       =default;
    ~PlayerClock()                              =default;

    // queries:
    value_type get_count() const { return count_; }
    name_type get_name() const {
        static char const nullified[] = "?nullified?";
        name_type name_or = name_.get();
        return name_or ? name_or : nullified;
    }

    // modifiers:
    void set_count(value_type count) { count_ = count; }
    void decrement() { --count_; }

private:
    name_holder name_;
    std::uint_least16_t count_;
};

extern PlayerClock pclk[];
extern void set_clocks();

std::ostream& operator<<(std::ostream&, const PlayerClock&);

#endif // include guard
