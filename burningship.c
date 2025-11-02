#include "fractol.h"

static int burning_ship_iter(t_complex c)
{
    t_complex z = {0, 0};
    int i = 0;

    while (i < 100)
    {
        z.re = fabs(z.re);
        z.im = fabs(z.im);
        z = c_mul(z, z);
        z = c_add(z, c);

        if (z.re * z.re + z.im * z.im > 4)
            break;
        i++;
    }
    return i;
}

static t_complex pixel_to_complex(int x, int y)
{
    t_complex c;
    c.re = (double)x / X_MAX * 3.4 - 2.2;
    c.im = (double)y / Y_MAX * 3.0 - 2.5;
    return c;
}

void draw_burning_ship(t_img *img)
{
    int x, y;
    t_complex c;
    int color;

    y = 0;
    while (y < Y_MAX)
    {
        x = 0;
        while (x < X_MAX)
        {
            c = pixel_to_complex(x, y);
            if (burning_ship_iter(c) == 100)
                color = 0x000000;
            else
                color = 0xFFFFFF;
            my_mlx_pixel_put(img, x, y, color);
            x++;
        }
        y++;
    }
}