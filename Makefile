# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/06 12:11:13 by trosinsk          #+#    #+#              #
#    Updated: 2024/02/10 01:49:17 by trosinsk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= fractol
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast #-fsanitize=address -g 
LIBMLX	:= ../../MLX42
SRCS 	:= main.c utils.c mandelbrot.c julia.c ft_atod.c hook_events.c
LIBFT	:= ./libft
PRINTF	:= ./printf
BONUS	:= bonus.c

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm 
INCLUDE := -L $(LIBFT) -lft -L $(PRINTF) -lftprintf
OBJS	:= ${SRCS:.c=.o}
BOBJS	:= ${BONUS:.c=.o}

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	make -C $(LIBFT)
	make -C $(PRINTF)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) $(INCLUDE) -o $(NAME)

bonus:
$(NAME): $(OBJS) $(BOBJS)
	make -C $(LIBFT)
	make -C $(PRINTF)
	@$(CC) $(OBJS) $(BOBJS) $(LIBS) $(HEADERS) $(INCLUDE) -o $(NAME)

clean:
	@rm -rf $(OBJS) $(BOBJS)
	@cd $(LIBFT) && $(MAKE) clean
	@cd $(PRINTF) && $(MAKE) clean
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx, bonus