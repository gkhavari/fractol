/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 16:49:41 by gkhavari          #+#    #+#             */
/*   Updated: 2025/11/04 16:49:47 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*sin goes from -1 to 1 (1 + sin) goes from 0 to 2 
multiplied by 127.5 goes from 0 to 255 for RGB colors
Phase shift r, g, b so that they peak at different times*/
static int	trippy_color(size_t iteration, size_t max_iter)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (iteration >= max_iter)
		return (0x000000);
	t = (double)iteration / (double)max_iter;
	r = (int)(127.5 * (1 + sin(2 * M_PI * t)));
	g = (int)(127.5 * (1 + sin(2 * M_PI * t + 2 * M_PI / 3)));
	b = (int)(127.5 * (1 + sin(2 * M_PI * t + 4 * M_PI / 3)));
	return ((r << 16) | (g << 8) | b);
}

/*square root, grows fast in the beginning and slower later
Early iterations → mostly red.
Mid iterations → red + green (orange/yellow).
Late iterations → red + green + blue (white-hot).*/
static int	fire_color(size_t iteration, size_t max_iter)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (iteration >= max_iter)
		return (0x000000);
	t = pow((double)iteration / (double)max_iter, 0.5);
	r = (int)(255 * fmin(1.0, 3.0 * t));
	g = (int)(255 * fmin(1.0, 3.0 * (t - 0.3)));
	b = (int)(255 * fmin(1.0, 3.0 * (t - 0.6)));
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	return ((r << 16) | (g << 8) | b);
}

/*Calculate with a polynomial */
static int	cosmic_color(size_t iteration, size_t max_iter)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (iteration >= max_iter)
		return (0x000000);
	t = (double)iteration / max_iter;
	r = (int)(9 * (1 - t) * t * t * t * 255);
	g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	b = (int)(9 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return ((r << 16) | (g << 8) | b);
}

int	get_color(t_app_state *state, size_t iteration)
{
	int		color;
	size_t	max_iter;

	max_iter = MAX_ITER;
	if (state->fractal.color_scheme == COSMIC)
		color = cosmic_color(iteration, max_iter);
	else if (state->fractal.color_scheme == FIRE)
		color = fire_color(iteration, max_iter);
	else if (state->fractal.color_scheme == TRIPPY)
		color = trippy_color(iteration, max_iter);
	else
		color = 0x000000;
	return (color);
}
