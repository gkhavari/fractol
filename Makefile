NAME    = fractol

SRCS    =	main.c \
			input.c \
			init.c \
			ft_atof.c \
			utils.c \
			utils_libft.c \
			utils_coords.c \
			draw_fractal.c \
			fractals.c \
			color.c \
			event_handler.c \
			key_events.c \
			mouse_events.c \
			handle_panning.c \
			shift_image.c \
			ft_memmove.c

OBJS    = $(SRCS:.c=.o)

CC      = cc
CFLAGS  = -Wall -Wextra -Werror

MLX_LIBS= -lXext -lX11 -lm -lz -lmlx

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(MLX_LIBS) -o $(NAME)
	@echo "✅ $(NAME) built!"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "✅ Created $@"

clean:
	@rm -f $(OBJS)
	@echo "🧹 Cleaned object files"

fclean: clean
	@rm -f $(NAME)
	@echo "🧹 Cleaned executable"

re: fclean all

.PHONY: all clean fclean re