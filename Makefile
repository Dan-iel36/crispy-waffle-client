.PHONY : all

all:  install compile build


compile:
	@gcc -c main.c -o main.o


build: compile
	@gcc main.o -o client

install: build
	@chmod +x client


clean:
	@rm -rf ./"*.o"
	@rm -rf client