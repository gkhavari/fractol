
#include "fractol.h"

int get_color(t_app_state state, )

int cosmic_color(int iteration, int max_iter)
{
    if (iteration >= max_iter)
        return 0x000000;

    double t = (double)iteration / max_iter;

    int r = (int)(127.5 * (1 + sin(6.2831 * t + 0.0)));
    int g = (int)(127.5 * (1 + sin(6.2831 * t + 2.0)));
    int b = (int)(127.5 * (1 + sin(6.2831 * t + 4.0)));

    r = (int)(r * 0.6);
    g = (int)(g * 0.3);
    b = (int)(b * 1.2);
    if (b > 255) b = 255;

    return ((r << 16) | (g << 8) | b);
}

int fire_color(int iteration, int max_iter)
{
    if (iteration >= max_iter)
        return 0x000000;

    double t = (double)iteration / max_iter;

    t = pow(t, 0.6);

    int r = (int)(255 * fmin(1.0, 3.0 * t));
    int g = (int)(255 * fmin(1.0, 3.0 * (t - 0.33)));
    int b = (int)(255 * fmin(1.0, 3.0 * (t - 0.66)));

    if (g < 0)
		g = 0;
    if (b < 0)
		b = 0;

    return ((r << 16) | (g << 8) | b);
}

int trippy_color(int iteration, int max_iter)
{
    if (iteration >= max_iter)
        return 0x000000;

    double t = (double)iteration / max_iter * M_PI * 2.0;

    int r = (int)(127.5 * (1 + sin(t)));
    int g = (int)(127.5 * (1 + sin(t + 2.094))); // +120°
    int b = (int)(127.5 * (1 + sin(t + 4.188))); // +240°

    return ((r << 16) | (g << 8) | b);
}