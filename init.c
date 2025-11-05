/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:29:32 by gkhavari          #+#    #+#             */
/*   Updated: 2025/11/05 17:29:34 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	set_fractal_type(char *input, t_app_state *state)
{
	t_fractal	f;

	if (ft_strcmp(input, "mandelbrot") == 0)
		f.fractal_type = MANDELBROT;
	else if (ft_strcmp(input, "julia") == 0)
		f.fractal_type = JULIA;
	else if (ft_strcmp(input, "burningship") == 0)
		f.fractal_type = BURNINGSHIP;
	else
		f.fractal_type = MANDELBROT;
	state->fractal = f;
}

void	set_fractal_range(t_app_state *state)
{
	if (state->fractal.fractal_type == MANDELBROT)
	{
		state->fractal.center.re = CENTER_RE_MANDELBROT;
		state->fractal.center.im = CENTER_IM_MANDELBROT;
		state->fractal.re_range = RE_RANGE_MANDELBROT;
	}
	else if (state->fractal.fractal_type == JULIA)
	{
		state->fractal.center.re = CENTER_RE_JULIA;
		state->fractal.center.im = CENTER_IM_JULIA;
		state->fractal.re_range = RE_RANGE_JULIA;
	}
	else if (state->fractal.fractal_type == BURNINGSHIP)
	{
		state->fractal.center.re = CENTER_RE_BURNINGSHIP;
		state->fractal.center.im = CENTER_IM_BURNINGSHIP;
		state->fractal.re_range = RE_RANGE_BURNINGSHIP;
	}
}

void	init_fractal(char **input, t_app_state *state)
{
	set_fractal_type(input[0], state);
	state->fractal.color_scheme = FIRE;
	state->fractal.max_iter = MAX_ITER;
	state->fractal.zoom = 1.0;
	if (state->fractal.fractal_type != JULIA)
	{
		state->fractal.c_julia.re = 0.0;
		state->fractal.c_julia.im = 0.0;
	}
	else
	{
		state->fractal.c_julia.re = ft_atof(input[1]);
		state->fractal.c_julia.im = ft_atof(input[2]);
	}
	set_fractal_range(state);
}

void	init_window(char *titel, t_app_state *state)
{
	void	*mlx;
	void	*mlx_win;
	t_img	mlx_img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, titel);
	mlx_img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	mlx_img.addr = mlx_get_data_addr(mlx_img.img,
			&mlx_img.bits_per_pixel, &mlx_img.line_length, &mlx_img.endian);
	state->mlx = mlx;
	state->win = mlx_win;
	state->image = mlx_img;
}
