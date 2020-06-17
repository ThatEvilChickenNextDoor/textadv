all: main.o events.o
	@g++ -std=c++17 -Wall -Wpedantic main.o events.o
main.o: events.hpp
	@g++ -c -o main.o main.cpp -std=c++17 -Wall -Wpedantic
events.o: events.hpp
	@g++ -c -o events.o events.cpp -std=c++17 -Wall -Wpedantic 
clean:
	@rm *.out *.o