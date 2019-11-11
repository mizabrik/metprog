CC=g++

LDFLAGS=-std=c++17
CXXFLAGS=-std=c++17

run: test
	./test

test: test.o

test.o: test.cc scatter.h catch.hpp

catch.hpp:
	wget https://github.com/philsquared/Catch/releases/download/v1.12.2/catch.hpp

.PHONY: clean
clean:
	rm -f test test.o catch.hpp
