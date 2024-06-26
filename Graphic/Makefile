##
## EPITECH PROJECT, 2024
## Zappy_Graphic
## File description:
## Makefile
##

GREEN  := \033[1;32m
YELLOW := \033[1;33m
BLUE   := \033[1;34m
RED    := \033[1;31m
RESET  := \033[0m

SRC_DIR := src

RAY_LIB := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -g3

COVERAGE_FLAGS := -fprofile-arcs -ftest-coverage

TSRCS = $(wildcard tests/unit-tests/*.cpp)

SRCS := $(wildcard \$(SRC_DIR)/Commands/*.cpp 	\
			$(SRC_DIR)/*.cpp 	\
			$(SRC_DIR)/Core/*.cpp 	\
			$(SRC_DIR)/Server/*.cpp 	\
			$(SRC_DIR)/Factory/*.cpp)

SRCS_NO_MAIN = $(filter-out src/Main.cpp, $(SRCS))

OBJS_NO_MAIN = $(SRCS_NO_MAIN:.c=.o)

INCLUDES := -I./src \
			-I./src/Interface \
			-I./src/Core \
			-I./src/Server \
			-I./src/Commands \
			-I./src/Factory \

OBJS := $(SRCS:.cpp=.o)
TOBJS = $(TSRCS:.cpp=.o)

TARGET := zappy_gui

TTarget := unit-tests

all: $(TARGET)

$(TTarget): $(TOBJS) $(OBJS_NO_MAIN)
	@echo -e "$(YELLOW)Compiling unit tests...$(RESET)"
	@$(CXX) -o $(TTarget) $(TOBJS) $(OBJS_NO_MAIN) $(RAY_LIB) -lcriterion $(INCLUDES) $(COVERAGE_FLAGS)
	@echo -e "$(GREEN)Unit tests compiled successfully!$(RESET)"

tests_run: $(TTarget)
	@echo -e "$(YELLOW)Running unit tests...$(RESET)"
	./$(TTarget)
	@gcovr -r . --exclude 'tests/*'
	@gcovr -r . --exclude 'tests/*' --html --html-details -o tests/coverage.html
	@echo -e "$(BLUE)Coverage report generated in coverage.html$(RESET)"

$(TARGET): $(OBJS)
	@echo -e "$(YELLOW)Linking object files to create the target...$(RESET)"
	@$(CXX) $(OBJS) -o $@ $(RAY_LIB) $(INCLUDES)
	@echo -e "$(GREEN)Build completed successfully!$(RESET)"

%.o: %.cpp
	@echo -e "$(BLUE)Compiling $<...$(RESET)"
	@$(CXX) -c $< -o $@ $(INCLUDES)
	@echo -ne "$(YELLOW)[$@]$(RESET) "

clean:
	@echo -e "$(RED)Cleaning object files...$(RESET)"
	@$(RM) $(OBJS) $(TOBJS)
	@$(RM) tests/*.html tests/*.css
	@$(RM) tests/unit-tests/*.gcda tests/unit-tests/*.gcno
	@$(RM) *.gcda *.gcno
	@echo -e "$(GREEN)Clean completed!$(RESET)"

fclean: clean
	@echo -e "$(RED)Removing target file...$(RESET)"
	@$(RM) $(TARGET) $(TTarget)
	@echo -e "$(GREEN)Full clean completed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
