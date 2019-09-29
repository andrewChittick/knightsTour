#Andrew Chittick
#makefile compiles knight

#enable c++11
CXXFLAGS = -std=c++11 

#make a knightsTour
knightsTour: main.o user.o tour.o
	g++ main.o user.o tour.o -o knightsTour

#make a main
main: main.cpp user.h tour.h
	g++ -c main.cpp

#make a user
user: user.cpp user.h
	g++ -c user.cpp

#make a tour
tour: tour.cpp tour.h
	g++ -c tour.cpp

#make clean
clean:
	rm -f *.o
	rm knightsTour

#make run
run: knightsTour
	./knightsTour

#end makefile
