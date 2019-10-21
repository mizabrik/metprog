CC=g++

run: test
	./test

test: test.o

test.o: test.cc readcsv.h catch.hpp

catch.hpp:
	wget https://raw.githubusercontent.com/catchorg/Catch2/master/single_include/catch2/catch.hpp

.PHONY: clean
clean:
	rm -f test test.o catch.hpp
