#include "fractol.h"

static int mandelbrot_iter(t_complex c)
{
    t_complex z = {0, 0};
    int i = 0;

    while (i < MAX_ITER)
    {
        z = c_mul(z, z);
        z = c_add(z, c);
        if (z.re * z.re + z.im * z.im > 4)
            break;
        i++;
    }
    return i;
}

t_complex mapping(int x, int y, t_complex center, double zoom)
{
    t_complex c;
    c.re = (x - X_MAX / 2.0) * zoom + center.re;
    c.im = (y - Y_MAX / 2.0) * zoom + center.im;
    return c;
}

int color_fire(int iter)
{
    if (iter == MAX_ITER)
        return 0x000000;

    double t = (double)iter / MAX_ITER;
    int r = (int)(255 * pow(t, 0.3));
    int g = (int)(128 * pow(t, 1.0));
    int b = (int)(32  * pow(t, 3.0));

    return (r << 16) | (g << 8) | b;
}

void draw_mandelbrot(t_img *img, t_fractal f)
{
    t_complex center = {-0.75, 0.0}; // nice central view
    double zoom = 0.003;              // smaller = zoom in
    int x, y, iter, color;
    t_complex c;

    y = 0;
    while (y < Y_MAX)
    {
        x = 0;
        while (x < X_MAX)
        {
            c = mapping(x, y, center, zoom);
            iter = mandelbrot_iter(c);
            color = (f.color)(iter);
            my_mlx_pixel_put(img, x, y, color);
            x++;
        }
        y++;
    }
}