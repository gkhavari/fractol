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
/*
static void	handel_panning(int key, t_app_state *state)
{
	double	re_step;
	double	im_step;

	re_step = (state->fractal.re_range / state->fractal.zoom) * PAN_FRACTION;
	im_step = re_step / ((double)WIDTH / HEIGHT);
	if (key == KEY_LEFT)
		state->fractal.center.re -= re_step;
	if (key == KEY_RIGHT)
		state->fractal.center.re += re_step;
	if (key == KEY_UP)
		state->fractal.center.im += im_step;
	if (key == KEY_DOWN)
		state->fractal.center.im -= im_step;
}*/

static void	shift_image(t_app_state *state, int shift_x, int shift_y)
{
	int bpp = state->image.bits_per_pixel / 8;
	int line_bytes = state->image.line_length;
	int img_size = line_bytes * HEIGHT;
	char	*row;
	int y;

	y = 0;
	if (shift_y != 0)
	{
		if (shift_y > 0)	// move image up
			ft_memmove(state->image.addr, state->image.addr + shift_y * line_bytes,	img_size - shift_y * line_bytes);
		else				// move image down
			ft_memmove(state->image.addr - shift_y * line_bytes, state->image.addr, img_size + shift_y * line_bytes);
	}
	if (shift_x != 0)
	{
		while (y < HEIGHT)
		{
			row = state->image.addr + y * line_bytes;
			if (shift_x > 0)	// move image left
				ft_memmove(row, row + shift_x * bpp, line_bytes - shift_x * bpp);
			else				// move image right
				ft_memmove(row - shift_x * bpp, row, line_bytes + shift_x * bpp);
			y++;
		}
	}
}

static t_region get_new_region(int shift_x, int shift_y)
{
	t_region	new_region;

	new_region = FULL_REGION;
	if (shift_x < 0)
		new_region.end_x = -shift_x;
	else if (shift_x > 0)
		new_region.start_x = WIDTH - shift_x;
	else if (shift_y < 0)
		new_region.end_y = - shift_y;
	else if (shift_y > 0)
		new_region.start_y = HEIGHT - shift_y;
	return (new_region);
}

static void	handle_panning2(int key, t_app_state *state)
{
	int	shift_x;
	int shift_y;
	t_region new_strip;
	t_complex center_delta;
	double re_range = state->fractal.re_range / state->fractal.zoom;
	double im_range = re_range * HEIGHT / WIDTH; // same as re_range / aspect_ratio


	shift_x = 0;
	shift_y = 0;
 
	if (key == KEY_RIGHT)
		shift_x = (int) (WIDTH * PAN_FRACTION);
	else if (key == KEY_LEFT)
		shift_x = - (int) (WIDTH * PAN_FRACTION);
	else if (key == KEY_UP)
		shift_y = - (int) (HEIGHT * PAN_FRACTION);
	else if (key == KEY_DOWN)
		shift_y = (int) (HEIGHT * PAN_FRACTION);
	shift_image(state, shift_x, shift_y);
	new_strip = get_new_region(shift_x, shift_y);
	center_delta.re = ((double)shift_x / (WIDTH - 1)) * re_range;
	center_delta.im = -((double)shift_y / (HEIGHT - 1)) * im_range;
	state->fractal.center = c_add(state->fractal.center, center_delta);
	draw_fractal(state, new_strip);
	mlx_put_image_to_window((*state).mlx, (*state).win,
		(*state).image.img, 0, 0);
}

static void	zoom_on_mouse(t_app_state *env,
	int mouse_x, int mouse_y, double zoom_factor)
{
	t_complex	mouse_pos;
	double		aspect_ratio;
	double		im_range;

	aspect_ratio = (double)HEIGHT / WIDTH;
	im_range = env->fractal.re_range * aspect_ratio;
	mouse_pos = pixel_to_complex(env, mouse_x, mouse_y);
	env->fractal.re_range *= zoom_factor;
	im_range = env->fractal.re_range * aspect_ratio;
	env->fractal.center.re = mouse_pos.re
		- ((double)mouse_x / WIDTH - 0.5) * env->fractal.re_range;
	env->fractal.center.im = mouse_pos.im
		+ ((double)mouse_y / HEIGHT - 0.5) * im_range;
}

int	key_event(int key, t_app_state *state)
{
	if (key == KEY_ESC)
		destroy_event(state);
	if (key == KEY_C)
	{
		state->fractal.color_scheme++;
		if (state->fractal.color_scheme > TRIPPY)
			state->fractal.color_scheme = COSMIC;
	}
	if (key == KEY_R)
	{
		state->fractal.zoom = 1.0;
		set_fractal_range(state);
	}
	if (key == KEY_PLUS1 || key == KEY_PLUS2)
		state->fractal.zoom *= ZOOM_FACTOR;
	if (key == KEY_MINUS1 || key == KEY_MINUS2)
		state->fractal.zoom /= ZOOM_FACTOR;
	if (key == KEY_LEFT || key == KEY_RIGHT || key == KEY_UP || key == KEY_DOWN)
	{
		handle_panning2(key, state);
		return (0);
	}
	draw_fractal(state, FULL_REGION);
	return (0);
}

int	mouse_event(int key, int x, int y, t_app_state *state)
{
	if (key == 4)
		zoom_on_mouse(state, x, y, 1 / ZOOM_FACTOR);
	else if (key == 5)
		zoom_on_mouse(state, x, y, ZOOM_FACTOR);
	draw_fractal(state, FULL_REGION);
	return (0);
}

int	destroy_event(t_app_state *state)
{
	if (state->image.img)
		mlx_destroy_image(state->mlx, state->image.img);
	exit(EXIT_SUCCESS);
}
