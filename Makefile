# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/28 14:19:08 by kaye              #+#    #+#              #
#    Updated: 2021/06/28 19:30:16 by kaye             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# COMPILATION

CC		= clang
CFLAGS 	= -Wall -Wextra -Werror
IFLAGS 	= -I./incs
LFLAGS	= -lpthread

# DIRECTORIES

BUILD 			:= .build
INC_DIR			:= incs
SRC_DIR 		:= srcs
OBJ_DIR 		:= $(BUILD)/obj
DIRS			:= $(OBJ_DIR) $(addprefix $(OBJ_DIR)/, $(SUB_DIR))

# FILES

NAME			:= philo
SRC				:= philosophers.c \
				   utils.c \
				   mini_lib.c \
				   mini_lib2.c \
				   mini_lib3.c
OBJ				:= $(SRC:%.c=$(OBJ_DIR)/%.o)

# COLORS

DEFAULT_COLOR	= \033[0m
BLACK_COLOR		= \033[1;30m
RED_COLOR		= \033[1;31m
GREEN_COLOR		= \033[1;32m
YELLOW_COLOR	= \033[1;33m
BLUE_COLOR		= \033[1;34m
MAGENTA_COLOR 	= \033[1;35m
CYAN_COLOR 		= \033[1;36m

# MAKEFILE

$(NAME): $(OBJ)
	@echo "Creating $(RED_COLOR) $(NAME) $(DEFAULT_COLOR)..."
	@$(CC) $(CFLAG) $(IFLAGS) $(OBJ) -o $@ $(LFLAGS)
	@echo "$(GREEN_COLOR)Compilation $(YELLOW_COLOR)of $(RED_COLOR)$(CLIENT) $(BLUE_COLOR)done$(DEFAULT_COLOR)"

all: $(NAME)

clean:
	rm -Rf $(BUILD)
fclean: clean
	rm -Rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

$(BUILD):
	@echo "Creating $(RED_COLOR)$@ $(DEFAULT_COLOR)..."
	@mkdir $@ $(DIRS);

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c | $(BUILD)
	@echo "Compiling $(CYAN_COLOR)$< $(DEFAULT_COLOR)..."
	@$(CC) $(CFLAG) $(IFLAGS) -c $< -o $@