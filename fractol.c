#include  "fractol.h"

#define ESC 65307

int	destroy_event(t_app_state *state)
{
	mlx_destroy_image(state->mlx, state->image.img);
	mlx_destroy_window(state->mlx, state->win);
	exit(EXIT_SUCCESS);
}

int	on_key_hook_event(int key, t_app_state *state)
{
	if (key == ESC)
		destroy_event(state);
//	draw_fractal(state);
	return (0);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= X_MAX || y < 0 || y >= Y_MAX)
		return;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/*int is_valid_julia_arg(char *str)
{
    int i = 0;
    int dot_count = 0;
    double val = 0;
    double frac = 0;
    int sign = 1;
    double divisor = 10.0;

    if (!str || str[0] == '\0')
        return 0;
    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    if (str[i] == '\0')
        return 0;
    while (str[i])
    {
        if (str[i] == '.')
        {
            dot_count++;
            if (dot_count > 1)
                return 0;
            i++;
            continue;
        }
        if (str[i] < '0' || str[i] > '9')
            return 0;
        if (dot_count == 0)
            val = val * 10 + (str[i] - '0');
        else
        {
            frac += (str[i] - '0') / divisor;
            divisor *= 10.0;
        }
        i++;
    }
    val = sign * (val + frac);
    if (val < -2.0 || val > 2.0)
        return 0;
    return 1;
}*/