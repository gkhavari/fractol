#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include <stdlib.h>
# include <math.h>
# include <unistd.h>

# define X_MAX 1920
# define Y_MAX 1080
# define MAX_ITER 300
//# define M_PI 3.14159265358979323846

#define ESC 65307

# define MANDELBROT 1
# define JULIA 2
# define BURNING_SHIP 3

# define COSMOS 7
# define FIRE 8
# define TRIPPY 9

typedef struct s_pixel
{
	int	x;
	int	y;
}	t_pixel;

typedef struct s_complex
{
    double re;
    double im;
} t_complex;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_fractal
{
	void (* draw)(t_fractal *f);
	int (* get_color)(int iter, int max_iter);
	int max_iter;
	double	zoom;
    double  escape_radius;
    t_complex   min;
	t_complex	max;
//    int     color_scheme;
} t_fractal;

typedef struct s_app_state {
	void		*mlx;
	void		*win;
	t_img		image;
	t_fractal	fractal;
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