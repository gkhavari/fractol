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

static int	cosmic_color(int iteration, int max_iter)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (iteration >= max_iter)
		return (0x000000);
	t = (double)iteration / max_iter;
	r = (int)(127.5 * (1 + sin(6.2831 * t + 0.0)));
	g = (int)(127.5 * (1 + sin(6.2831 * t + 2.0)));
	b = (int)(127.5 * (1 + sin(6.2831 * t + 4.0)));
	r = (int)(r * 0.6);
	g = (int)(g * 0.3);
	b = (int)(b * 1.2);
	if (b > 255)
		b = 255;
	return ((r << 16) | (g << 8) | b);
}

static int	fire_color(int iteration, int max_iter)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (iteration >= max_iter)
		return (0x000000);
	t = (double)iteration / max_iter;
	t = pow(t, 0.6);
	r = (int)(255 * fmin(1.0, 3.0 * t));
	g = (int)(255 * fmin(1.0, 3.0 * (t - 0.33)));
	b = (int)(255 * fmin(1.0, 3.0 * (t - 0.66)));
	if (g < 0)
		g = 0;
	if (b < 0)
		b = 0;
	return ((r << 16) | (g << 8) | b);
}

static int	trippy_color(int iteration, int max_iter)
{
	double	t;
	int		r;
	int		g;
	int		b;

	if (iteration >= max_iter)
		return (0x000000);
	t = (double)iteration / max_iter;
	r = (int)(127.5 * (1 + sin(t)));
	g = (int)(127.5 * (1 + sin(t + 2.094))); // +120°
	b = (int)(127.5 * (1 + sin(t + 4.188))); // +240°
	return ((r << 16) | (g << 8) | b);
}

int	get_color(t_app_state state, int iteration, int max_iter)
{
	int	color;

	if (state.fractal.color_scheme == COSMIC)
		color = cosmic_color(iteration, max_iter);
	else if (state.fractal.color_scheme == FIRE)
		color = fire_color(iteration, max_iter);
	else if (state.fractal.color_scheme == TRIPPY)
		color = trippy_color(iteration, max_iter);
	else
		color = 0x000000;
	return (color);
}
