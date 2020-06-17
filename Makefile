all: main.o events.o
	@g++ -Wall -Wpedantic main.o events.o
main.o: events.hpp
	@g++ -c -o main.o main.cpp -Wall -Wpedantic
events.o: events.hpp
	@g++ -c -o events.o events.cpp -Wall -Wpedantic 
clean:
	@rm *.out *.o