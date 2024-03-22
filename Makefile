cc=g++
cc=g++-13

std=c++11
std=c++20
std=c++23

warn=-Wall -Wextra -Werror -pedantic
warn=

b=debug
flags=-mavx -mavx2
flags=-mavx
flags=


all: main

debug:
	$(eval flags+=-g)

release:
	$(eval flags+=-O3)

main: Makefile main.cpp
	$(cc) -std=$(std) $(flags) main.cpp -o main $(warn)

run: $(b) main
	./main

