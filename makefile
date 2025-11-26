CXX = g++
CXXFLAGS = -std=c++11 -Wall -fopenmp

OBJS = src/main.o src/body/body.o src/kosmos/kosmos.o src/test/orbit.o

all: nbody_simulator

nbody_simulator: $(OBJS)
	$(CXX) $(CXXFLAGS) -o nbody_simulator $(OBJS)

src/main.o: src/main.cpp
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o src/main.o

src/body/body.o: src/body/body.cpp src/body/body.hpp
	$(CXX) $(CXXFLAGS) -c src/body/body.cpp -o src/body/body.o

src/kosmos/kosmos.o: src/kosmos/kosmos.cpp src/kosmos/kosmos.hpp
	$(CXX) $(CXXFLAGS) -c src/kosmos/kosmos.cpp -o src/kosmos/kosmos.o

src/test/orbit.o: src/test/orbit.cpp src/test/orbit.h
	$(CXX) $(CXXFLAGS) -c src/test/orbit.cpp -o src/test/orbit.o

run: all
	./nbody_simulator

clean:
	rm -f src/main.o src/body/body.o src/kosmos/kosmos.o src/test/orbit.o nbody_simulator