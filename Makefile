CXX      ?= g++
CXXFLAGS ?= -std=c++17 -Wall -Wextra -O2
SRC      := main.cpp Gioco.cpp Tabellone.cpp Input.cpp

monopoly: $(SRC) $(wildcard *.h)
	$(CXX) $(CXXFLAGS) $(SRC) -o $@

clean:
	rm -f monopoly
