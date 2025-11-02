#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include <stdlib.h>
# include <math.h>
# include <unistd.h>

# define X_MAX 1920
# define Y_MAX 1080
# define MAX_ITER 300

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_complex
{
    double re;
    double im;
} t_complex;

typedef struct s_fractal
{
	void (* draw)(t_fractal *f);
	int (* get_color)(int iter, int max_iter);
	int max_iter;
	double	zoom;
	t_complex	*center;
    t_complex   *c;
    double  escape_radius;
//    int     color_scheme;
} t_fractal;

typedef struct s_app_state {
    t_img       mlx;
    t_fractal   fractal;
    int         width;
    int         height;
    t_complex   min;
	t_complex	max;
//    int         color_scheme;
//    bool        julia_follow_mouse;
}   t_app_state;

void	ft_putstr_fd(char *s, int fd);
t_complex mapping(int x, int y, t_complex center, double zoom);
void	draw_mandelbrot(t_img *img, t_fractal f);
void	draw_julia(t_img *img, t_complex c);
t_complex c_add(t_complex a, t_complex b);
t_complex c_mul(t_complex a, t_complex b);
double	ft_atof(const char *str);
int ft_strcmp(const char *s1, const char *s2);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
int color_fire(int iter);




#endif