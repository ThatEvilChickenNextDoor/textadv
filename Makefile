CFLAGS=-std=c++2a -Wall -Wextra -Wpedantic -lncurses
ifdef CROSS
	CC=x86_64-w64-mingw32-g++-posix
	CFLAGS += -I/mnt/c/tools/msys64/mingw64/include -L/mnt/c/tools/msys64/mingw64/lib -static
else
	CC=g++
endif
DEPS = events.hpp globals.hpp
OBJ = main.o events.o 

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

textadv.out: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

cursed: cursed.cpp
	$(CC) cursed.cpp $(CFLAGS)
.PHONY=clean
clean:
	rm *.out *.o *.exe