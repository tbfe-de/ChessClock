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

template<typename T>
class PlayerClock {
    using value_type = T;
public:
    // construction and destruction:
    PlayerClock(std::string const& name, value_type count)
        : name_{name}, count_{count}
    {}
    PlayerClock()                               =delete;
    PlayerClock(PlayerClock const&)             =default;
//  PlayerClock& operator=(PlayerClock const&) // implemented below
    PlayerClock(PlayerClock&&)                  =default;
    PlayerClock& operator=(PlayerClock&&)       =default;
    ~PlayerClock()                              =default;

    // queries:
    auto get_name() const { return name_; }
    operator value_type() const { return count_; }

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
    std::string const name_;
    value_type count_;
};

// to make the `PlayerClock` completely independent from the
// counter type used the template instantiation should be moved
// to the chess clock application (actual change postponed)
//
extern PlayerClock<std::uint_least16_t> pclk[3];

// when the chess clock array is wrapped into a class this should
// become a member function
//
extern void set_clocks();

template<typename T>
std::ostream& operator<<(std::ostream &strm, const PlayerClock<T>& clk) {
    extern char const* ticker_indicator;
    std::ostream os{strm.rdbuf()};
    os.fill('0');
    os << '\r' << *ticker_indicator
        << ' ' << clk.get_name()
        << ' ' << std::setw(2) << clk/60
        << ':' << std::setw(2) << clk%60;
    os.flush();
    return strm;
}

#endif // include guard
