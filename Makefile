#-------------------------------------------------------------------------------
# Central Makefile for Ariadne
#-------------------------------------------------------------------------------

CXX = clang++

CXXFLAGS = -Wall -Wextra -pedantic -O3 -g -c -std=c++14
LDFLAGS = -lstdc++ -lboost_system -lboost_filesystem

#LINUXFLAGS = -target x86_64-linux-gnu
#MACFLAGS = -target x86_64-darwin

EXECUTABLE = ariadne.exe

SOURCES = main.cpp geometry.cpp input.cpp types.cpp routing.cpp
OBJECTS = main.o geometry.o input.o types.o routing.o

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $+ $(LDFLAGS) -o $@

main.o: main.cpp main.hpp types.hpp input.hpp routing.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

geometry.o: geometry.cpp geometry.hpp matrix.hpp types.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

input.o: input.cpp input.hpp types.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

types.o: types.cpp types.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

routing.o: routing.cpp routing.hpp matrix.hpp types.hpp geometry.hpp
	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -f *.o && rm -f $(EXECUTABLE)
