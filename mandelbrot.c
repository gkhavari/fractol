#include "fractol.h"

static int mandelbrot_iter(t_complex c)
{
    t_complex z = {0, 0};
    int i = 0;

    while (i < 100)
    {
        z = c_mul(z, z);
        z = c_add(z, c);
        if (z.re * z.re + z.im * z.im > 4)
            break;
        i++;
    }
    return i;
}

t_complex pixel_to_complex(int x, int y)
{
    t_complex c;
    c.re = (double)x / X_MAX * 3.5 - 2.5; // map to [-2.5, 1.0]
    c.im = (double)y / Y_MAX * 2.0 - 1.0; // map to [-1.0, 1.0]
    return c;
}

void	draw_mandelbrot(t_img *img)
{
	int x;
	int y;
	t_complex c;
	int color;

	x = 0;
	y = 0;
	while (y < Y_MAX)
	{
		while (x < X_MAX)
		{
			c = pixel_to_complex(x, y);
			if (mandelbrot_iter(c) == 100)
				color = 0x000000;
			else
				color = 0xFFFFFF;
			my_mlx_pixel_put(img, x, y, color);
			x++;
		}
		x=0;
		y++;
	}
}