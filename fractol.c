#include  "fractol.h"

#define ESC 65307

void	free_fractal(t_fractal *f)
{
	free(f->c);
	free(f);
}

int handle_key(int keycode)
{
    if (keycode == ESC)
    {
        exit(0);
    }
    return (0);
}

int handle_close(void)
{
    exit(0);
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

t_fractal	*parse_fractal(char **argv)
{
	t_fractal *f;

	f = malloc(sizeof(t_fractal));
    if (!f)
           return (NULL);
    f->c = malloc(sizeof(t_complex));
    if (!f->c)
    {
        free(f);
        return (NULL);
    }
	if (ft_strcmp(argv[1], "mandelbrot") == 0)
	{
		f->name = "mandelbrot";
		(f->c)->re = 0;
		(f->c)->im = 0;
	}
	else if (ft_strcmp(argv[1], "julia") == 0)
	{
		f->name = "julia";
		(f->c)->re = ft_atof(argv[2]);
		(f->c)->im = ft_atof(argv[3]);
	}
	else
	{
		free_fractal(f);
		return (NULL);
	}
	return (f);
}

int is_valid_julia_arg(char *str)
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
}

int	check_input(int argc, char **argv)
{
	if (argc == 2 && ft_strcmp(argv[1], "mandelbrot") == 0)
		return (0);
	if (argc == 4 && ft_strcmp(argv[1], "julia") == 0)
	{
		if (is_valid_julia_arg(argv[2]) && is_valid_julia_arg(argv[3]))
			return (0);
		else
			return (1);
	}
	if (argc == 2 && ft_strcmp(argv[1], "burningship") == 0)
		return (0);
	if (argc == 2 && ft_strcmp(argv[1], "tricorn") == 0)
		return (0);
	return (1);
}

void	draw_fractal(t_img *img, t_fractal *f)
{
	if (ft_strcmp(f->name, "mandelbrot") == 0)
		draw_mandelbrot(img);
	else if (ft_strcmp(f->name, "julia") == 0)
		draw_julia(img, *f->c);
}

int	main(int argc, char **argv)
{
	void	*mlx;
	void	*mlx_win;
	t_img	mlx_img;
	t_fractal	*f;

	if (check_input(argc, argv))
	{
        ft_putstr_fd("Usage:\n", 2);
        ft_putstr_fd("  ./fractol mandelbrot\n", 2);
        ft_putstr_fd("  ./fractol julia <real> <imag> (range -2 to 2)\n", 2);
        ft_putstr_fd("  ./fractol burningship\n", 2);
        ft_putstr_fd("  ./fractol tricorn\n", 2);
        return (1);
    }
	f = parse_fractal(argv);
	if (!f)
		return (1);
	mlx = mlx_init();
	if (!mlx)
		return (free_fractal(f), 1);
	mlx_win = mlx_new_window(mlx, X_MAX, Y_MAX, argv[1]);
	if (!mlx_win)
		return (free_fractal(f), 1);
	mlx_img.img = mlx_new_image(mlx, X_MAX, Y_MAX);
	if (!mlx_img.img)
	{
    	mlx_destroy_window(mlx, mlx_win);
    	free_fractal(f);
    	return (1);
	}
	mlx_img.addr = mlx_get_data_addr(mlx_img.img,
			&mlx_img.bits_per_pixel, &mlx_img.line_length, &mlx_img.endian);
	draw_fractal(&mlx_img, f);
	mlx_put_image_to_window(mlx, mlx_win, mlx_img.img, 0, 0);
    mlx_key_hook(mlx_win, handle_key, NULL);
	mlx_hook(mlx_win, 17, 0L, handle_close, NULL);
	mlx_loop(mlx);
	mlx_destroy_image(mlx, mlx_img.img);
	mlx_destroy_window(mlx, mlx_win);
	free_fractal(f);
	return (0);
}