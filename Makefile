# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cgrasser <cgrasser@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/02 23:21:39 by cgrasser          #+#    #+#              #
#    Updated: 2024/12/11 09:30:58 by cgrasser         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

CC = cc
CFLAGS = -Wall -Wextra -Werror -g 
RM = rm -rf

SRC_DIR = src/
INC_DIR = include/
OBJ_DIR = build/

SRC = pipex.c utils.c

BOLD = \033[1m
GREEN = \033[32m
YELLOW = \033[93m
RESET = \033[0m

OBJS = $(SRC:%.c=$(OBJ_DIR)/%.o)

LIBFT_PATH = ./libft
LIBFT = $(LIBFT_PATH)/libft.a

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@$(CC) $(CFLAGS) -I$(LIBFT_PATH)/include -I ./include -c $< -o $@

bonus: all

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	@echo "$(YELLOW) ➥ $(RESET)$(BOLD) pipex $(GREEN)✔$(RESET)"

$(LIBFT):
	@make -s -C $(LIBFT_PATH)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

clean:
	@make -s -C $(LIBFT_PATH) clean
	@echo "$(YELLOW) ➥ $(RESET)$(BOLD)Cleaned all object files ! $(GREEN)✔$(RESET)"
	@$(RM) $(OBJ_DIR)

fclean:
	@make -s -C $(LIBFT_PATH) fclean
	@$(RM) $(OBJ_DIR)
	@echo "$(YELLOW) ➥ $(RESET)$(BOLD)Cleaned all object files ! $(GREEN)✔$(RESET)"
	@$(RM) $(NAME)
	@echo "$(YELLOW) ➥ $(RESET)$(BOLD)Cleaned push_swap ! $(GREEN)✔$(RESET)"

re: fclean all

.PHONY: all clean fclean re libft

