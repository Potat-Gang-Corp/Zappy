##
## EPITECH PROJECT, 2024
## Zappy_Graphic
## File description:
## Makefile
##

GREEN  := \033[0;32m
YELLOW := \033[1;33m
BLUE   := \033[1;34m
RED    := \033[0;31m
RESET  := \033[0m

LOADING_CHARS = \| / - \\

SRC_DIR := src

SRCS := $(wildcard $(SRC_DIR)/*.cpp)

INCLUDES := -I./src

OBJS := $(SRCS:.cpp=.o)

TARGET := zappy_graphic

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo -e "$(YELLOW)Linking object files to create the target...$(RESET)"
	@$(CXX) $(OBJS) -o $@ -lraylib -lm -lpthread -ldl -lrt -lX11 $(INCLUDES)
	@echo -e "$(GREEN)Build completed successfully!$(RESET)"

%.o: %.cpp
	@echo -e "$(BLUE)Compiling $<...$(RESET)"
	@$(CXX) -c $< -o $@ -lraylib -lm -lpthread -ldl -lrt -lX11 $(INCLUDES)
	@echo -ne "$(YELLOW)[$@]$(RESET) "

clean:
	@echo -e "$(RED)Cleaning object files...$(RESET)"
	@$(RM) $(OBJS)
	@echo -e "$(GREEN)Clean completed!$(RESET)"

fclean: clean
	@echo -e "$(RED)Removing target file...$(RESET)"
	@$(RM) $(TARGET)
	@echo -e "$(GREEN)Full clean completed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re
