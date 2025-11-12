/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 16:52:07 by gkhavari          #+#    #+#             */
/*   Updated: 2025/11/11 15:33:40 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	change_color(t_app_state *state)
{
	state->fractal.color_scheme++;
	if (state->fractal.color_scheme > TRIPPY)
		state->fractal.color_scheme = COSMIC;
}

void	reset_coord(t_app_state *state)
{
	set_fractal_range(state);
}

int	destroy_event(t_app_state *state, int exit_status)
{
	if (state->image.img)
		mlx_destroy_image(state->mlx, state->image.img);
	if (state->win)
		mlx_destroy_window(state->mlx, state->win);
	if (state->mlx)
		mlx_destroy_display(state->mlx);
	free(state->mlx);
	exit(exit_status);
}

int	destroy_event_wrapper(t_app_state *state)
{
	destroy_event(state, EXIT_SUCCESS);
	return (0);
}
