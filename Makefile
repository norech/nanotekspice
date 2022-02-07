##
## EPITECH PROJECT, 2022
## nanotekspice
## File description:
## Makefile
##

CC = g++

CFLAGS = -W -Wall -Werror -std=c++20 -g

LFLAGS = 

TEST_FLAGS = $(LFLAGS) -lgtest -lgcov -lpthread --coverage -fprofile-arcs -ftest-coverage

TARGET = nanotekspice

TARGET_TEST = unit_tests

SRC =	\

TESTS =	\

OBJ_TESTS = $(SRC:.cpp=.o) $(TESTS:.cpp=.o)

OBJ = $(SRC:.cpp=.o) src/main.o

all: $(TARGET)

build_all: ${OBJ}
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LFLAGS)

tests_run: clean_tests ${OBJ_TESTS}
	$(CC) $(CFLAGS) $(TEST_FLAGS) -o $(TARGET_TEST) $(OBJ_TESTS) $(LFLAGS)
	./$(TARGET_TEST) --verbose

coverage:
	gcovr -b --exclude-directories tests
	gcovr -r . --exclude-directories tests

clean_tests:
	rm -rf $(TARGET_TEST)

$(TARGET): build_all

clean:
	rm -f $(TARGET)

fclean: clean
	rm -f $(OBJ)
	rm -f *.gc* unit_tests

re: fclean all

.PHONY: all re tests_run coverage clean fclean
