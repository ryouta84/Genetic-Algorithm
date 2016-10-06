OBJS	= main.o GA.o
PROGRAM = main

all:			$(PROGRAM)

$(PROGRAM):		$(OBJS)
				g++  $(OBJS) -o $(PROGRAM)

main.o:			main.cpp
				g++ -std=c++14 -c main.cpp


GA.o: 			GA.cpp
				g++ -std=c++14 -c GA.cpp
