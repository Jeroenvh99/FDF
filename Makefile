NAME = fdf
CFLAGS = -Wall -Werror -Wextra
OBJS = ${SRCS:.c=.o}
BONUS_OBJS = ${BONUS_SRCS:.c=.o}
SRCS = main.c \
	parse_utils.c \
	error_utils.c \
	parse_input.c \
	input_utils.c \
	image_utils.c \
	draw_utils.c \
	hooks.c \
	hooks_utils.c \
	legend.c \
	setup.c
BONUS_SRCS = 

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -j -C ./libft add_bonus
	cmake -S ./MLX42 -B ./MLX42/build
	cmake --build ./MLX42/build -j4
	cc $(OBJS) $(CFLAGS) ./libft/libft.a ./MLX42/build/libmlx42.a -Iinclude -ldl -lglfw -pthread -lmd -lm -o $(NAME)

clean:
	$(MAKE) -j -C ./libft fclean
	cmake --build ./MLX42/build --target clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: clean fclean all bonus re

test:
	cc libfttester.c libft.a && ./a.out
