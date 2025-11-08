/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shift_image.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:17:07 by gkhavari          #+#    #+#             */
/*   Updated: 2025/11/08 17:17:09 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	shift_image_vertically(t_app_state *state, int shift_y)
{
	int		line_bytes;
	int		img_size;

	line_bytes = state->image.line_length;
	img_size = line_bytes * HEIGHT;
	if (shift_y == 0)
		return ;
	if (shift_y > 0)
		ft_memmove(state->image.addr,
			state->image.addr + shift_y * line_bytes,
			img_size - shift_y * line_bytes);
	else
		ft_memmove(state->image.addr - shift_y * line_bytes,
			state->image.addr,
			img_size + shift_y * line_bytes);
}

static void	shift_row_horizontally(char *row, int line_bytes,
		int bpp, int shift_x)
{
	if (shift_x == 0)
		return ;
	if (shift_x > 0)
		ft_memmove(row,
			row + shift_x * bpp,
			line_bytes - shift_x * bpp);
	else
		ft_memmove(row - shift_x * bpp,
			row,
			line_bytes + shift_x * bpp);
}

static void	shift_image_horizontally(t_app_state *state, int shift_x)
{
	int		bpp;
	int		line_bytes;
	int		y;
	char	*row;

	if (shift_x == 0)
		return ;
	bpp = state->image.bits_per_pixel / 8;
	line_bytes = state->image.line_length;
	y = 0;
	while (y < HEIGHT)
	{
		row = state->image.addr + y * line_bytes;
		shift_row_horizontally(row, line_bytes, bpp, shift_x);
		y++;
	}
}

void	shift_image(t_app_state *state, int shift_x, int shift_y)
{
	shift_image_horizontally(state, shift_x);
	shift_image_vertically(state, shift_y);
}
