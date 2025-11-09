/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_coords.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:18:34 by gkhavari          #+#    #+#             */
/*   Updated: 2025/11/08 17:18:36 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_region	set_region(int x_min, int x_max, int y_min, int y_max)
{
	t_region	region;

	region.start_x = x_min;
	region.end_x = x_max;
	region.start_y = y_min;
	region.end_y = y_max;
	return (region);
}

t_complex	pixel_to_complex(const t_app_state *state, int x, int y)
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
