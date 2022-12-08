/* C++ module implementation
 ===============================================================================
 Chess Clock Application
 ===============================================================================
 ...
*/

// own header file always goes first
#include "chessclock_app.h"

// project specific header files (alphabetically sorted)
#include "player.h"
#include "player_clock.h"
#include "ticker_thread.h"
#include "utils.h"

// standard library header files (alphabetically sorted)
#include <cstddef> // std::size_t
#include <iostream>

std::ofstream aux_tty{}; // <------ should go before ...
std::ostream aux_out{std::cout.rdbuf()}; // ... this one
std::future<void> clockwork;

void toggle_player() {
    if (aux_tty) aux_out.put('\n');
    switch (active) {
        case Player::WHITE: active = Player::BLACK; break;
        case Player::BLACK: active = Player::WHITE; break;
    }
}

void show_clocks(unsigned which) {
    using std::size_t;
    aux_out << "+ ------------------------------\n";
    if (which & (1<<(size_t)Player::NONE))
        aux_out << pclk[(size_t)Player::NONE] << " preset" << std::endl;
    if (which & (1<<(size_t)Player::WHITE))
        aux_out << pclk[(size_t)Player::WHITE] << " initial" << std::endl;
    if (which & (1<<(size_t)Player::BLACK))
        aux_out << pclk[(size_t)Player::BLACK] << " initial" << std::endl;
}

bool reset(std::string const& str) {
    using std::size_t;
    pclk[(size_t)Player::NONE].count =
        parse_mins_secs(str, pclk[(size_t)Player::NONE].count);
    set_clocks();
    auto selected = ((1<<(size_t)Player::WHITE) | (1<<(size_t)Player::BLACK));
    if (!str.empty()) selected |= (1<<(size_t)Player::NONE);
    show_clocks(selected);
    return true;
}

bool start(std::string const&) {
    using std::size_t;
    if ((pclk[(size_t)Player::WHITE].count == 0)
     || (pclk[(size_t)Player::BLACK].count == 0)) {
        std::cout << "! not yet (re-)set to start time\n";
    }
    else {
        active = Player::WHITE;
        clockwork = std::async(ticker_thread);
    }
    return true;
}
