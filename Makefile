kilo: src/main.cpp src/terminal.o src/terminal.h
	$(CXX) src/main.cpp src/terminal.o -o kilo.out -Wall -Wextra -pedantic -std=c++11
