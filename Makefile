# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/02 23:21:39 by cgrasser          #+#    #+#              #
#    Updated: 2024/12/03 16:13:42 by cgrasser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -rf

SRC_DIR = src/
INC_DIR = include/
OBJ_DIR = build/

SRC = main.c

BOLD = \033[1m
GREEN = \033[32m
YELLOW = \033[93m
RESET = \033[0m

OBJS = $(SRC:%.c=$(OBJ_DIR)/%.o)

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) -I$(LIBFT_PATH)/include -c $< -o $@

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJS)
	@$(CC) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(YELLOW) ➥ $(RESET)$(BOLD) pipex $(GREEN)✔$(RESET)"

$(LIBFT):
	@make -s -C $(LIBFT_PATH)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@make -s -C $(LIBFT_PATH) clean
	@echo "$(YELLOW) ➥ $(BOLD)Cleaned all object files ! $(GREEN)✔$(RESET)\n"
	@$(RM) $(OBJ_DIR)

fclean:
	@make -s -C $(LIBFT_PATH) fclean
	@$(RM) $(OBJ_DIR)
	@echo "$(YELLOW) ➥ $(RESET)$(BOLD)Cleaned all object files ! $(GREEN)✔$(RESET)"
	@$(RM) $(NAME)
	@echo "$(YELLOW) ➥ $(RESET)$(BOLD)Cleaned push_swap ! $(GREEN)✔$(RESET)"

re: fclean all

.PHONY: all clean fclean re libft

