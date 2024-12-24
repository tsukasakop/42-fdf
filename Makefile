# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkondo <tkondo@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/09 00:35:59 by tkondo            #+#    #+#              #
#    Updated: 2024/12/23 20:26:42 by tkondo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
INCLUDE_DIR = -Iinclude -I$$HOME/include
CFLAGS = -c -fPIE -Wall -Wextra -Werror -static-libsan

SRC_DIR = src
OBJ_DIR = bin
LIB_DIR = -L$$HOME/lib -Llib
LIBS = -lm -lmlx_Linux -lmlx -lXext -lX11 -lft
NAME = fdf 
TARGET =\
	main

OBJS = $(addprefix $(OBJ_DIR)/,$(addsuffix .o,$(TARGET)))

all: $(NAME)

dev: CFLAGS+=-O0 -g -fsanitize=address
dev: all

$(NAME): $(OBJS)
	$(CC) $^ -o $@ $(LIB_DIR) $(LIBS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -o $@ $(INCLUDE_DIR)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

devre: fclean dev

.PHONY: dev devre all clean fclean re init
