# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/06 12:11:13 by trosinsk          #+#    #+#              #
#    Updated: 2024/02/11 02:45:35 by trosinsk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= fractol
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast -g #-fsanitize=address
LIBMLX	:= ./MLX42
SRCS 	:= main.c utils.c mandelbrot.c julia.c ft_atod.c mouse_hooks.c key_hooks.c
LIBFT	:= ./libft
BONUS	:= bonus.c

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm 
INCLUDE := -L $(LIBFT) -lft
OBJS	:= ${SRCS:.c=.o}
BOBJS	:= ${BONUS:.c=.o}

all: libmlx $(NAME)

libmlx:
	git clone https://github.com/codam-coding-college/MLX42.git 
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	make -C $(LIBFT)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) $(INCLUDE) -o $(NAME)

bonus:
$(NAME): $(OBJS) $(BOBJS)
	make -C $(LIBFT)
	@$(CC) $(OBJS) $(BOBJS) $(LIBS) $(HEADERS) $(INCLUDE) -o $(NAME)

clean:
	@rm -rf $(OBJS) $(BOBJS)
	@cd $(LIBFT) && $(MAKE) clean
	@rm -rf MLX42

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx, bonus