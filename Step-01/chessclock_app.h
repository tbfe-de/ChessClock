/* C++ header file
 ===============================================================================
 Chess Clock Application
 ===============================================================================
 ...
*/

#ifndef CHESSCLOCK_APP_H_
#define CHESSCLOCK_APP_H_

// project specific header files (alphabetically sorted)
#include "player_clock.h"
#include "ticker_thread.h"

// standard library header files (alphabetically sorted)
#include <fstream>
#include <future>
#include <ostream>
#include <string>

extern std::ofstream aux_tty;
extern std::ostream aux_out;
extern std::future<void> clockwork;

extern void toggle_player();
extern void show_clocks(unsigned);
extern bool reset(std::string const&);
extern bool start(std::string const&);

#endif // include guard
