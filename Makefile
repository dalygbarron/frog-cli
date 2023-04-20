CXX=g++
OUT=frog
CXXFLAGS=-Wall -g -std=c++11
LDLIBS=-lncurses

%.o: %.cc *.h

frog: main.o Render.o Map.o Dude.o
	$(CXX) $(CXXFLAGS) $(LDLIBS) -o $(OUT) *.o

clean:
	rm *.o $(OUT)