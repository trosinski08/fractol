NAME	:= fractol
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast -g #-fsanitize=address
LIBMLX	:= ./MLX42
SRCS 	:= main.c utils.c mandelbrot.c julia.c ft_atod.c mouse_hooks.c key_hooks.c bonus.c effects.c
LIBFT	:= ./libft

HEADERS	:= -I ./include -I $(LIBMLX)/include
LIBS	:= $(LIBMLX)/build/libmlx42.a -ldl -lglfw -pthread -lm 
INCLUDE := -L $(LIBFT) -lft
OBJS	:= ${SRCS:.c=.o}

all: libmlx $(NAME)

libmlx:
	@if [ ! -d "$(LIBMLX)" ]; then \
		git clone https://github.com/codam-coding-college/MLX42.git; \
	fi
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(NAME): $(OBJS)
	make -C $(LIBFT)
	@$(CC) $(OBJS) $(LIBS) $(HEADERS) $(INCLUDE) -o $(NAME)

clean:
	@rm -rf $(OBJS)
	@cd $(LIBFT) && $(MAKE) clean
	@rm -rf MLX42

fclean: clean
	@rm -rf $(NAME)
	@cd $(LIBFT) && $(MAKE) fclean

re: clean all

.PHONY: all clean fclean re libmlx