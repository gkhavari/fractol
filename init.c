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
	if (ft_strcmp(input, "mandelbrot") == 0)
		state->fractal.fractal_type = MANDELBROT;
	else if (ft_strcmp(input, "julia") == 0)
		state->fractal.fractal_type = JULIA;
	else if (ft_strcmp(input, "burningship") == 0)
		state->fractal.fractal_type = BURNINGSHIP;
	else
		state->fractal.fractal_type = MANDELBROT;
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
	if (state->fractal.fractal_type == JULIA)
	{
		state->fractal.c_julia.re = ft_atof(input[1]);
		state->fractal.c_julia.im = ft_atof(input[2]);
	}
	set_fractal_range(state);
}

void	init_window(char *title, t_app_state *state)
{
	ft_bzero(state, sizeof(*state));
	state->mlx = mlx_init();
	if (!state->mlx)
		destroy_event(state, EXIT_FAILURE);
	state->win = mlx_new_window(state->mlx, WIDTH, HEIGHT, title);
	if (!state->win)
		destroy_event(state, EXIT_FAILURE);
	state->image.img = mlx_new_image(state->mlx, WIDTH, HEIGHT);
	if (!state->image.img)
		destroy_event(state, EXIT_FAILURE);
	state->image.addr = mlx_get_data_addr(state->image.img,
			&state->image.bits_per_pixel, &state->image.line_length,
			&state->image.endian);
	if (!state->image.addr)
		destroy_event(state, EXIT_FAILURE);
}
