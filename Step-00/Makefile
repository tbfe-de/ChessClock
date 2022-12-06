EXE= chess-clock

run: $(EXE)
	@./$(EXE)

$(EXE): main.cpp
	g++ -std=c++17 *.cpp -o $@

clean:
	rm -f $(EXE) a.out core *.o
