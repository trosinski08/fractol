# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: trosinsk <trosinsk@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/06 12:11:13 by trosinsk          #+#    #+#              #
#    Updated: 2024/02/07 20:21:00 by trosinsk         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# CC := cc
# CFLAGS := -Wall -Wextra -Werror
# LDFLAGS := -lglfw -L"/Users/aguediri/.brew/opt/glfw/lib/" -framework Cocoa -framework OpenGL -framework IOKit #-fsanitize=address -g 

# bonus:
# clean:
# fclean:
# re:
NAME	:= fractol
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast
LIBMLX	:= ../../MLX42
SRCS 	:= main.c utils.c mandelbrot.c julia.c ft_atod.c hook_events.c
LIBFT	:= ./libft
PRINTF	:= ./printf

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm
INCLUDE = -L $(LIBFT) -lft -L $(PRINTF) -lftprintf
OBJS	:= ${SRCS:.c=.o}

all: libmlx $(NAME)

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	make -C $(LIBFT)
	make -C $(PRINTF)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) $(INCLUDE) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@cd $(LIBFT) && $(MAKE) clean
	@cd $(PRINTF) && $(MAKE) clean
	@rm -rf $(LIBMLX)/build

fclean: clean
	@rm -rf $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, libmlx