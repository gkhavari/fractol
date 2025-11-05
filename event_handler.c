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

static void	panning(int key, t_app_state *state)
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
		panning(key, state);
	draw_fractal(state);
	return (0);
}

int	mouse_event(int key, int x, int y, t_app_state *env)
{
	if (key == 4)
		zoom_on_mouse(env, x, y, 1 / ZOOM_FACTOR);
	else if (key == 5)
		zoom_on_mouse(env, x, y, ZOOM_FACTOR);
	draw_fractal(env);
	return (0);
}

int	destroy_event(t_app_state *state)
{
	if (state->image.img)
		mlx_destroy_image(state->mlx, state->image.img);
	exit(EXIT_SUCCESS);
}
