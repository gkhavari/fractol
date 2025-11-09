NAME    = fractol

SRCS    = main.c init.c ft_atof.c utils.c utils_libft.c utils_coords.c event_handler.c events.c draw_fractal.c fractals.c color.c handle_panning.c shift_image.c
OBJS    = $(SRCS:.c=.o)

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -O3

MLX_LIBS= -lXext -lX11 -lm -lz -lmlx

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(MLX_LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I/usr/include -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re