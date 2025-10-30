#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include <stdlib.h>
# include <math.h>
# include <unistd.h>

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef enum e_dim
{
	X_MAX = 1920,
	Y_MAX = 1080
}	t_dim;

typedef struct s_complex
{
    double re;
    double im;
} t_complex;

typedef struct s_fractal
{
    char    *name;
    t_complex   *c;
} t_fractal;

void	ft_putstr_fd(char *s, int fd);
t_complex pixel_to_complex(int x, int y);
void	draw_mandelbrot(t_img *img);
void	draw_julia(t_img *img, t_complex c);
t_complex c_add(t_complex a, t_complex b);
t_complex c_mul(t_complex a, t_complex b);
double	ft_atof(const char *str);
int ft_strcmp(const char *s1, const char *s2);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);



#endif