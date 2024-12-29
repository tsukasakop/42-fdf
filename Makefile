# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkondo <tkondo@student.42tokyo.jp>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/09 00:35:59 by tkondo            #+#    #+#              #
#    Updated: 2024/12/29 10:59:48 by tkondo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
INCLUDE_DIR = -Iinclude -I./libft/include -I./libmlx
CFLAGS = -c -fPIE -Wall -Wextra -Werror -static-libsan -DDEBUG=1

SRC_DIR = src
OBJ_DIR = bin
LIBS = libft/libft.a libmlx/libmlx.a
LIB_DIR = -L./libft -L./libmlx
LFLAGS = -lm -lmlx -lXext -lX11 -lft
#LFLAGS = -lm -lmlx -lXext -lX11 -lft -fsanitize=address
NAME = fdf 
CANVAS_W = $(shell expr $$(xdpyinfo | awk '/dimensions/{print $$2}' | awk -Fx '{print $$1}') / 2)
CANVAS_H = $(shell expr $$(xdpyinfo | awk '/dimensions/{print $$2}' | awk -Fx '{print $$2}') / 2)
TARGET =\
	main\
	parse\
	hook\

OBJS = $(addprefix $(OBJ_DIR)/,$(addsuffix .o,$(TARGET)))

all: $(NAME)

dev: CFLAGS+=-O0 -g -fsanitize=address
dev: LFLAGS+=-g -fsanitize=address
dev: all

$(NAME): $(LIBS) $(OBJS)
	$(CC) $^ -o $@ $(LIB_DIR) $(LFLAGS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $< -o $@ $(INCLUDE_DIR) -D CANVAS_W=$(CANVAS_W) -D CANVAS_H=$(CANVAS_H)

libft/libft.a:
	make -C libft

libmlx/libmlx.a:
	make -C libmlx

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

devre: fclean dev

.PHONY: dev devre all clean fclean re init
