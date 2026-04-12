.PHONY: all run clean

PROGRAM = lab2
SRC = src/main.cpp
CXXFLAGS = -std=c++17 -Wall -I include -mmacosx-version-min=15.0
#CXXFLAGS = -std=c++17 -Wall -I include

all: $(PROGRAM)

$(PROGRAM): $(SRC)
	g++ $(CXXFLAGS) $(SRC) -o $(PROGRAM)

run: $(PROGRAM)
	./$(PROGRAM)

clean:
	rm -f $(PROGRAM)