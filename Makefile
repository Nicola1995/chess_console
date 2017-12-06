OPTIONS=-c -Wall -std=c++11 

all: chess


chess: main.o
	g++ main.o Desk.o Validator.o -o chess

main.o: main.cpp Desk.o Validator.o
	g++ $(OPTIONS) main.cpp	

Desk.o: Desk.cpp Desk.h
	g++ $(OPTIONS) Desk.cpp

Validator.o: Validator.cpp Validator.h
	g++ $(OPTIONS) Validator.cpp	
