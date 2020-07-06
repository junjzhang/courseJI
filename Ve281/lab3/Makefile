all: main

main: alg.o main.o
	g++ -std=c++11 -O2 -Wall -g -o main alg.o main.o

alg.o: alg.cpp
	g++ -std=c++11 -O2 -Wall -g -c alg.cpp

main.o: main.cpp
	g++ -std=c++11 -O2 -Wall -g -c main.cpp

clean:
	rm -f main *.o