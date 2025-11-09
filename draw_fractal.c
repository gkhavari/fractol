/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fractal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:43:17 by gkhavari          #+#    #+#             */
/*   Updated: 2025/11/05 17:43:19 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*state->image.addr pointer to the start of the image data
One row of pixels takes up line_length bytes
move down y rows: y * line_length.
Each pixel within a row takes up (bits_per_pixel / 8) bytes.
move x pixels across in that row: x * (bits_per_pixel / 8).*/
static void	put_pixel(t_app_state *state, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = state->image.addr + (y * state->image.line_length
			+ x * (state->image.bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}

static int	get_iteration(const t_app_state *state, t_complex c)
{
	int		fractal_type;
	size_t	iteration;

	iteration = 0;
	fractal_type = state->fractal.fractal_type;
	if (fractal_type == MANDELBROT)
		iteration = mandelbrot(c);
	else if (fractal_type == JULIA)
		iteration = julia(c, state->fractal.c_julia);
	else if (fractal_type == BURNINGSHIP)
		iteration = burningship(c);
	return (iteration);
}

void	draw_fractal(t_app_state *state, t_region region)
{
	int			x;
	int			y;
	int			color;
	t_complex	c;

	y = region.start_y;
	while (y < region.end_y)
	{
		x = region.start_x;
		while (x < region.end_x)
		{
			c = pixel_to_complex(state, x, y);
			color = get_color(state, get_iteration(state, c));
			put_pixel(state, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(state->mlx, state->win,
		state->image.img, 0, 0);
}
