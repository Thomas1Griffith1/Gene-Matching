CC = g++
DEBUG = -g
CFLAGS = -Wall -std=gnu++11 $(DEBUG)
LFLAGS = -Wall $(DEBUG)

compile: lab12.out

lab12.out: lab12.cpp
	$(CC) $(CFLAGS) -o lab12.out lab12.cpp

run: lab12.out
	./lab12.out

clean:
	rm *.out
