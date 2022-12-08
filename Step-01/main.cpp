#include "chessclock_app.h"
#include "cli_menu.h"
#include "utils.h"

#include <iostream>

int main(int argc, char *argv[]) {
    if (auto aux_name = std::getenv("CHESSCLOCK_AUX_TTY")) {
        aux_tty.open(aux_name);
        if (aux_tty) {
            aux_out.rdbuf(aux_tty.rdbuf());
        }
    }
    if (aux_tty) aux_out.put('\n');
    if (argc > 1) parse_mins_secs(argv[1]);
    std::cout << "* Welcome from the Chess-Clock *" << std::endl;
    do {} while (menu({
        { "R = (re-)set to <mins>:<secs>\n"
          "    or last start value used", reset },
        { "S = start a game (first white)", start },
        { "Q = end program", quit },
    }));
    std::cout << "* The Chess-Clock says Goodbye *" << std::endl;
}
