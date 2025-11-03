#include "fractol.h"

void	init_fractal(char **input, t_app_state *env)
{
	t_fractal f;

	if (ft_strcmp(input[0], "mandelbrot") == 0)
		f.draw = init_mandelbrot(input);
	else if (ft_strcmp(input[0], "julia") == 0)
		f.draw = init_julia(input);
	else if ("burningship" == 0)
		f.draw = init_burningship(input);
	env->fractal = f;
}

t_img	init_window(char *titel, t_app_state *env)
{
	void	*mlx;
	void	*mlx_win;
	t_img	mlx_img;

	mlx = mlx_init();
	//TODO: Error handling
	mlx_win = mlx_new_window(mlx, X_MAX, Y_MAX, titel);
	//TODO: Error handling
	mlx_img.img = mlx_new_image(mlx, X_MAX, Y_MAX);
	//TODO: Error handling
	mlx_img.addr = mlx_get_data_addr(mlx_img.img,
			&mlx_img.bits_per_pixel, &mlx_img.line_length, &mlx_img.endian);
	env->mlx = mlx;
	env->win = mlx_win;
	env->image = mlx_img;
}