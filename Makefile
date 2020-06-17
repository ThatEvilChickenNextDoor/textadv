all: main.o events.o
	g++ -std=c++17 -Wall -Wpedantic main.o events.o
main.o: globals.hpp events.hpp main.cpp
	g++ -c -o main.o main.cpp -std=c++17 -Wall -Wpedantic
events.o: globals.hpp events.hpp events.cpp
	g++ -c -o events.o events.cpp -std=c++17 -Wall -Wpedantic 
clean:
	rm *.out *.o