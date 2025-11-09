/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:52:05 by gkhavari          #+#    #+#             */
/*   Updated: 2025/11/05 17:52:07 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	redraw_full_fractal(t_app_state *state)
{
	t_region	full_region;

	full_region = set_region(0, WIDTH, 0, HEIGHT);
	draw_fractal(state, full_region);
}

int	key_event(int key, t_app_state *state)
{
	if (key == KEY_ESC)
		destroy_event(state, EXIT_SUCCESS);
	else if (key == KEY_C)
		change_color(state);
	else if (key == KEY_R)
		reset_coord(state);
	else if (key == KEY_PLUS1 || key == KEY_PLUS2)
		state->fractal.zoom *= ZOOM_FACTOR;
	else if (key == KEY_MINUS1 || key == KEY_MINUS2)
		state->fractal.zoom /= ZOOM_FACTOR;
	else if (key == KEY_LEFT || key == KEY_RIGHT
		|| key == KEY_UP || key == KEY_DOWN)
		return (handle_panning(key, state), 0);
	redraw_full_fractal(state);
	return (0);
}

int	mouse_event(int key, int x, int y, t_app_state *state)
{
	if (key == MOUSE_SCROLL_UP)
		zoom_on_mouse(state, x, y, 1 / ZOOM_FACTOR);
	else if (key == MOUSE_SCROLL_DOWN)
		zoom_on_mouse(state, x, y, ZOOM_FACTOR);
	else if (key == LEFT_CLICK)
		change_center(state, x, y);
	redraw_full_fractal(state);
	return (0);
}
