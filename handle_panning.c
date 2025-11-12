/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_panning.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:53:02 by gkhavari          #+#    #+#             */
/*   Updated: 2025/11/08 16:53:08 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static t_region	get_new_region(int shift_x, int shift_y)
{
	t_region	new_region;

	new_region = set_region(0, WIDTH, 0, HEIGHT);
	if (shift_x < 0)
		new_region.end_x = -shift_x;
	else if (shift_x > 0)
		new_region.start_x = WIDTH - shift_x;
	if (shift_y < 0)
		new_region.end_y = -shift_y;
	else if (shift_y > 0)
		new_region.start_y = HEIGHT - shift_y;
	return (new_region);
}

/*(0, 0) is top left corner, so up is negativ and down positiv*/
static void	get_shift_from_key(int key, int *shift_x, int *shift_y)
{
	*shift_x = 0;
	*shift_y = 0;
	if (key == KEY_RIGHT || key == KEY_D)
		*shift_x = (int)(WIDTH * PAN_FRACTION);
	else if (key == KEY_LEFT || key == KEY_A)
		*shift_x = - (int)(WIDTH * PAN_FRACTION);
	else if (key == KEY_UP || key == KEY_W)
		*shift_y = - (int)(HEIGHT * PAN_FRACTION);
	else if (key == KEY_DOWN || key == KEY_S)
		*shift_y = (int)(HEIGHT * PAN_FRACTION);
}

/*minus sign DOWN increases pixel coordinates but decrease complex coordinate
WIDTH/HEIGHT go from 0 to WIDTH/HEIGHT - 1*/
static void	update_center(t_app_state *state, int shift_x, int shift_y)
{
	t_complex	center_delta;
	double		re_range;
	double		im_range;

	re_range = state->fractal.re_range;
	im_range = re_range * HEIGHT / WIDTH;
	center_delta.re = ((double)shift_x / (WIDTH - 1)) * re_range;
	center_delta.im = -((double)shift_y / (HEIGHT - 1)) * im_range;
	state->fractal.center = c_add(state->fractal.center, center_delta);
}

void	handle_panning(int key, t_app_state *state)
{
	int			shift_x;
	int			shift_y;
	t_region	new_strip;

	get_shift_from_key(key, &shift_x, &shift_y);
	shift_image(state, shift_x, shift_y);
	new_strip = get_new_region(shift_x, shift_y);
	update_center(state, shift_x, shift_y);
	draw_fractal(state, new_strip);
	mlx_put_image_to_window((*state).mlx, (*state).win,
		(*state).image.img, 0, 0);
}
