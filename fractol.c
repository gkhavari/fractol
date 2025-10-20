/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 18:41:05 by gkhavari          #+#    #+#             */
/*   Updated: 2025/10/20 18:41:08 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= X_MAX || y < 0 || y >= Y_MAX)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	draw_circle(t_img *img, int cx, int cy, int radius, int color)
{
	int	x;
	int	y;

	x = -radius;
	y = -radius;
	while (y <= radius)
	{
		while (x <= radius)
		{
			if (x * x + y * y <= radius * radius)
				my_mlx_pixel_put(img, cx + x, cy + y, color);
			x++;
		}
		x = -radius;
		y++;
	}
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_img	mlx_img;

	mlx = mlx_init();
	if (!mlx)
		return (1);
	mlx_win = mlx_new_window(mlx, X_MAX, Y_MAX, "Hello World");
	if (!mlx_win)
		return (1);
	mlx_img.img = mlx_new_image(mlx, X_MAX, Y_MAX);
	if (!mlx_img.img)
		return (1);
	mlx_img.addr = mlx_get_data_addr(mlx_img.img,
			&mlx_img.bits_per_pixel, &mlx_img.line_length, &mlx_img.endian);
	draw_circle(&mlx_img, X_MAX / 2, Y_MAX / 2, 200, 0x00FFFFFF);
	mlx_put_image_to_window(mlx, mlx_win, mlx_img.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
