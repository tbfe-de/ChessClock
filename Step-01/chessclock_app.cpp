#include "chessclock_app.h"

#include "player.h"
#include "utils.h"

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
        show_single_clock(aux_out, NONE) << " preset" << std::endl;
    if (which & (1<<WHITE))
        show_single_clock(aux_out, WHITE) << " initial" << std::endl;
    if (which & (1<<BLACK))
        show_single_clock(aux_out, BLACK) << " initial" << std::endl;
}

bool reset(std::string const& str) {
    parse_mins_secs(str);
    set_clocks();
    auto selected = (1<<WHITE) | (1<<BLACK);
    if (!str.empty()) selected |= (1<<NONE);
    show_clocks(selected);
    return true;
}

bool start(std::string const&) {
    if ((pclk[WHITE].count == 0)
     || (pclk[BLACK].count == 0)) {
        std::cout << "! not yet (re-)set to start time\n";
    }
    else {
        active = WHITE;
        clockwork = std::async(ticker_thread);
    }
    return true;
}
