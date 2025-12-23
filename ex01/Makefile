NAME := RPN
CXX := c++
CXXFLAGS := -Wall -Wextra -Werror -std=c++98 -pedantic
SRC := main.cpp RPN.cpp
OBJ := $(SRC:%.cpp=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o : %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) *.o

fclean: clean
	$(RM) $(NAME)

format:
	clang-format -i *.h *.cpp

linter:
	clang-tidy *.cpp -- -isysroot $(shell xcrun --show-sdk-path) -I. -std=c++98

re: fclean all

.PHONY: all clean re fclean format linter
