CXX 	 = g++
CXXFLAGS = -std=c++14 -Wall
OBJS	 = main.o GA.o
PROGRAM  = main

all:			$(PROGRAM)

$(PROGRAM):		$(OBJS)
				$(CXX) $(OBJS) -o $(PROGRAM)

main.o:			main.cpp
				$(CXX) $(CXXFLAGS) -c $^

GA.o: 			GA.cpp GA.hpp
				$(CXX) $(CXXFLAGS) -c GA.cpp

clean:
				$(RM) $(OBJS)
