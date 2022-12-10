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

void toggle_player() {
    if (aux_tty) aux_out.put('\n');
    switch (active) {
        case WHITE: active = BLACK; break;
        case BLACK: active = WHITE; break;
    }
}

void show_clocks(unsigned which) {
    aux_out << "+ ------------------------------\n";
    if (which & (1<<NONE))
        aux_out << pclk[NONE] << " preset" << std::endl;
    if (which & (1<<WHITE))
        aux_out << pclk[WHITE] << " initial" << std::endl;
    if (which & (1<<BLACK))
        aux_out << pclk[BLACK] << " initial" << std::endl;
}

bool reset(std::string const& str) {
    pclk[NONE] = parse_mins_secs(str, pclk[NONE]);
    set_clocks();
    auto selected = (1<<WHITE) | (1<<BLACK);
    if (!str.empty()) selected |= (1<<NONE);
    show_clocks(selected);
    return true;
}

bool start(std::string const&) {
    if ((pclk[WHITE] == 0)
     || (pclk[BLACK] == 0)) {
        std::cout << "! not yet (re-)set to start time\n";
    }
    else {
        active = WHITE;
        clockwork = std::async(ticker_thread);
    }
    return true;
}
