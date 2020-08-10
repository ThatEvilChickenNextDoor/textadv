CC=g++
CFLAGS=-std=c++2a -Wall -Wextra -Wpedantic
DEPS = events.hpp globals.hpp
OBJ = main.o events.o 

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

textadv.out: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY=clean
clean:
	rm *.out *.o