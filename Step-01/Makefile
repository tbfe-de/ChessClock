EXE= chessclock_app

COMPILE=g++ -std=c++17 -c
LINK=g++ -std=c++17

run: $(EXE)
	@./$(EXE) $(args)

MAIN_OBJS=\
	cli_menu.o\
	chessclock_app.o\
	ticker_thread.o\
	player.o\
	player_clock.o\
	utils.o\
	main.o
$(EXE): $(MAIN_OBJS)
	$(LINK) $(MAIN_OBJS) -o $@

MAIN_INCL=\
	utils.h\
	cli_menu.h\
	chessclock_app.h
main.o: $(MAIN_INCL) main.cpp
	$(COMPILE) main.cpp

CHESSCLOCK_APP_H=\
	chessclock_app.h
CLI_MENU_H=\
	cli_menu.h
PLAYER_CLOCK_H=\
	player_clock.h
PLAYER_H=\
	player.h
TICKER_THREAD_H=\
	ticker_thread.h

CHESSCLOCK_APP_INCL=\
	$(PLAYER_H)\
	$(UTILS_H)\
	$(CHESSCLOCK_H)
chessclock_app.o: $(CHESSCLOCK_APP_INCL) chessclock_app.cpp
	$(COMPILE) chessclock_app.cpp

CLI_MENU_INCL=\
	$(CHESSCLOCK_H)\
	$(CLI_MENU)
cli_menu.o: $(CLI_MENU_INCL) cli_menu.cpp
	$(COMPILE) cli_menu.cpp

PLAYER_INCL=\
	$(PLAYER_H)
player.o: $(PLAYER_INCL) player.cpp
	$(COMPILE) player.cpp

PLAYER_CLOCK_INCL=\
	$(PLAYER_CLOCK_H)
player_clock.o: $(PLAYER_CLOCK_INCL) player_clock.cpp
	$(COMPILE) player_clock.cpp

TICKER_THREAD_INCL=\
	$(CHESSCLOCK_APP_H)\
	$(PLAYER)\
	$(PLAYER_CLOCK)\
	$(TICKER_THREAD_H)
ticker_thread.o: $(TICKER_THREAD_INCL) ticker_thread.cpp
	$(COMPILE) ticker_thread.cpp

UTILS_INCL=\
	$(PLAYER_H)\
	$(PLAYER_CLOCK_H)\
	$(UTILS_H)
utils.o: $(UTILS_INCL) utils.cpp
	$(COMPILE) -c utils.cpp

clean:
	rm -f $(EXE) a.out core *.o
