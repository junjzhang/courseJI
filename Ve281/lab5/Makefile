all: main

main: main.o
	g++ -std=c++11 -O2 -Wall -g -o main main.o

main.o: main.cpp
	g++ -std=c++11 -O2 -Wall -g -c main.cpp

clean:
	rm -f main *.o
