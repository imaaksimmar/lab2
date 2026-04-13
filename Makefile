.PHONY: all run test clean

CXXFLAGS = -std=c++17 -Wall -I include -mmacosx-version-min=15.0

PROGRAM = lab2
SRC = src/main.cpp

TEST_PROGRAM = run_tests
TEST_SRC = tests/run_tests.cpp tests/test.cpp

all: $(PROGRAM)

$(PROGRAM): $(SRC)
	g++ $(CXXFLAGS) $< -o $@

test: $(TEST_PROGRAM)
	./$(TEST_PROGRAM)

$(TEST_PROGRAM): $(TEST_SRC)
	g++ $(CXXFLAGS) $^ -o $@

run: $(PROGRAM)
	./$(PROGRAM)

clean:
	rm -f $(PROGRAM) $(TEST_PROGRAM)