/* C++ module implementation
 ===============================================================================
 Chess Clock Ticker Thread
 ===============================================================================
 ...
*/

// own header file always goes first
#include "ticker_thread.h"

// project specific header files (alphabetically sorted)
#include "chessclock_app.h"
#include "player.h"
#include "player_clock.h"

// standard library header files (alphabetically sorted)
#include <chrono>
#include <cstddef> // std::size_t
#include <iostream>
#include <thread>

char const ticker_symbols[] = {
        '|',  '/', '-', '\\',
        '|',  '/', '-', '\\', };
auto const N_TICKER_SYMBOLS = sizeof(ticker_symbols);
static_assert(N_TICKER_SYMBOLS == 8);
char const *ticker_indicator = &ticker_symbols[0];

void ticker_thread() {
    using std::size_t;
    auto step = std::chrono::steady_clock::now();
    int phase = 0;
    while ((pclk[(size_t)player::WHITE].count > 0)
        && (pclk[(size_t)player::BLACK].count > 0)) {
        phase = (phase + 1) % N_TICKER_SYMBOLS;
        ticker_indicator = &ticker_symbols[phase];
        if (phase == 0) --pclk[(size_t)(player)active].count;
        aux_out << pclk[(size_t)(player)active];
        using namespace std::chrono_literals;
        static_assert(1000 % N_TICKER_SYMBOLS == 0,
                      "otherwise clock skew will accumulate");
        step += 1000ms / N_TICKER_SYMBOLS;
        std::this_thread::sleep_until(step);
    }
    switch (active) {
        case player::WHITE:
            aux_out << "\r| WHITE time expired\n"
                    << pclk[(size_t)player::BLACK];
            break;
        case player::BLACK:
            aux_out << "\r| BLACK time expired\n"
                    << pclk[(size_t)player::WHITE];
            break;
        default:
            break;
    }
    aux_out << " (wins)" << std::endl;
    std::cout << "hit <Return> to continue" << std::flush;
    active = player::NONE;
}
