NAME    = fractol

SRCS    = main.c init.c ft_atof.c utils.c utils_libft.c utils_coords.c event_handler.c events.c draw_fractal.c fractals.c color.c handle_panning.c shift_image.c
OBJS    = $(SRCS:.c=.o)

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -O3 -g

MLX_DIR = minilibx-linux
MLX     = -L$(MLX_DIR) -lmlx_Linux
MLX_INC = -I$(MLX_DIR)
MLX_LIBS= -lXext -lX11 -lm -lz

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(MLX) $(MLX_LIBS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(MLX_INC) -I/usr/include -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re