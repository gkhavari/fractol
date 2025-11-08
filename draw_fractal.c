/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fractal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:43:17 by gkhavari          #+#    #+#             */
/*   Updated: 2025/11/05 17:43:19 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	pixel_to_complex(t_app_state *state, int x, int y)
{
	t_complex	c;
	double		aspect_ratio;
	double		re_range;
	double		im_range;

	aspect_ratio = (double)WIDTH / HEIGHT;
	re_range = state->fractal.re_range / state->fractal.zoom;
	im_range = re_range / aspect_ratio;
	c.re = state->fractal.center.re - re_range / 2
		+ ((double)x / (WIDTH - 1)) * re_range;
	c.im = state->fractal.center.im + im_range / 2
		- ((double)y / (HEIGHT - 1)) * im_range;
	return (c);
}

void	put_pixel(t_app_state *state, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = state->image.addr + (y * state->image.line_length
			+ x * (state->image.bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

int	get_iteration(t_app_state *state, t_complex c)
{
	int		fractal_type;
	size_t	iteration;

	iteration = 0;
	fractal_type = state->fractal.fractal_type;
	if (fractal_type == MANDELBROT)
		iteration = mandelbrot(c);
	else if (fractal_type == JULIA)
		iteration = julia(c, state->fractal.c_julia);
	else if (fractal_type == BURNINGSHIP)
		iteration = burningship(c);
	return (iteration);
}

void	draw_fractal(t_app_state *state, t_region region)
{
	int			x;
	int			y;
	int			color;
	t_complex	c;

	y = region.start_y;
	while (y < region.end_y)
	{
		x = region.start_x;
		while (x < region.end_x)
		{
			c = pixel_to_complex(state, x, y);
			color = get_color(state, get_iteration(state, c));
			put_pixel(state, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window((*state).mlx, (*state).win,
		(*state).image.img, 0, 0);
}
