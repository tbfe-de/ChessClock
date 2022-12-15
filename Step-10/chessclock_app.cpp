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
#include <iostream>

std::ofstream aux_tty{}; // <------ should go before ...
std::ostream aux_out{std::cout.rdbuf()}; // ... this one
std::future<void> clockwork;

bool toggle_player(std::string const &) {
    if (active == Player::NONE) return true;
    if (aux_tty) aux_out.put('\n');
    switch (active) {
        case Player::WHITE: active = Player::BLACK; break;
        case Player::BLACK: active = Player::WHITE; break;
    }
    return true;
}

void show_clocks(unsigned which) {
    aux_out << "+ ------------------------------\n";
    if (which & (1<<Player::NONE))
        aux_out << pclk[Player::NONE] << " preset" << std::endl;
    if (which & (1<<Player::WHITE))
        aux_out << pclk[Player::WHITE] << " initial" << std::endl;
    if (which & (1<<Player::BLACK))
        aux_out << pclk[Player::BLACK] << " initial" << std::endl;
}

bool reset(std::string const& str) {
    if (active != Player::NONE) return true;
    if (clockwork.valid()) clockwork.get();
    pclk[Player::NONE] = parse_mins_secs(str, pclk[Player::NONE]);
    pclk.set();
    auto selected = (1<<Player::WHITE) | (1<<Player::BLACK);
    if (!str.empty()) selected |= (1<<Player::NONE);
    show_clocks(selected);
    return true;
}

bool start(std::string const&) {
    if (active != Player::NONE) return true;
    if (clockwork.valid()) clockwork.get();
    if (pclk[Player::WHITE].expired()
     or pclk[Player::BLACK].expired()) {
        std::cout << "! not yet (re-)set to start time\n";
    }
    else {
        active = Player::WHITE;
        clockwork = std::async(ticker_thread);
    }
    return true;
}
