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
	t = sqrt((double)iteration / (double)max_iter);
	r = (int)(255 * fmax(0.0, fmin(1.0, 3.0 * t)));
	g = (int)(255 * fmax(0.0, fmin(1.0, 3.0 * (t - 0.3))));
	b = (int)(255 * fmax(0.0, fmin(1.0, 3.0 * (t - 0.6))));
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
	r = (int)(255 * fmin(1.0, 9 * (1 - t) * t * t * t));
	g = (int)(255 * fmin(1.0, 15 * (1 - t) * (1 - t) * t * t));
	b = (int)(255 * fmin(1.0, 9 * (1 - t) * (1 - t) * (1 - t) * t));
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
