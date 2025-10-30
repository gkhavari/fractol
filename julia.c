#include "fractol.h"

int julia_iter(t_complex z, t_complex c)
{
	int i = 0;

	while (i < 100)
	{
		z = c_add(c_mul(z, z), c);
		if (z.re * z.re + z.im * z.im > 4)
			break;
		i++;
	}
	return (i);
}

void	draw_julia(t_img *img, t_complex c)
{
	int x;
	int y;
	t_complex z;
	int iter;
	int color;

	y = 0;
	while (y < Y_MAX)
	{
		x = 0;
		while (x < X_MAX)
		{
			z = pixel_to_complex(x, y);
			iter = julia_iter(z, c);
			if (iter == 100)
				color = 0x000000;
			else
				color = 0xFFFFFF;
			my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		y++;
	}
}