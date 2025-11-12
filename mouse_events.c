/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_events.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:33:47 by gkhavari          #+#    #+#             */
/*   Updated: 2025/11/11 15:33:49 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*GOAL: Mouse pointer points at the same position 
on the complex plane before and after zooming

set re_range and im_range to zoomed values
new center = mouse_position - offset 
(+offset for imaginary because it faces down)
offset ((x or y)/(WIDTH or HEIGHT) - 0.5) * range // 0.5 is center*/
void	zoom_on_mouse(t_app_state *state,
	int mouse_x, int mouse_y, double zoom_factor)
{
	t_complex	mouse_pos;
	double		aspect_ratio;
	double		im_range;

	aspect_ratio = (double)HEIGHT / WIDTH;
	mouse_pos = pixel_to_complex(state, mouse_x, mouse_y);
	state->fractal.re_range *= zoom_factor;
	im_range = state->fractal.re_range * aspect_ratio;
	state->fractal.center.re = mouse_pos.re
		- ((double)mouse_x / WIDTH - 0.5) * state->fractal.re_range;
	state->fractal.center.im = mouse_pos.im
		+ ((double)mouse_y / HEIGHT - 0.5) * im_range;
}

void	change_center(t_app_state *state, int mouse_x, int mouse_y)
{
	t_complex	mouse_pos;

	mouse_pos = pixel_to_complex(state, mouse_x, mouse_y);
	state->fractal.center = mouse_pos;
}
