/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:52:19 by gkhavari          #+#    #+#             */
/*   Updated: 2025/11/05 17:52:23 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "mlx.h"
# include <stdlib.h>
# include <math.h>
# include <unistd.h>

# define WIDTH  800
# define HEIGHT 800
# define MAX_ITER 1000
# define ESCAPE_RADIUS_SQUARED 4.0
# define ZOOM_FACTOR 1.2
# define PAN_FRACTION 0.05
# define M_PI 3.14159265358979323846

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1

# define KEY_ESC 65307
# define KEY_C 99
# define KEY_R 114
# define KEY_PLUS1 93
# define KEY_PLUS2 65451
# define KEY_MINUS1 47
# define KEY_MINUS2 65453
# define KEY_LEFT 65361
# define KEY_UP 65362
# define KEY_RIGHT 65363
# define KEY_DOWN 65364
# define LEFT_CLICK 1
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5

# define MANDELBROT 1
# define JULIA 2
# define BURNINGSHIP 3

# define COSMIC 7
# define FIRE 8
# define TRIPPY 9

# define CENTER_RE_MANDELBROT -0.75
# define CENTER_IM_MANDELBROT 0.0
# define RE_RANGE_MANDELBROT 3.5

# define CENTER_RE_JULIA 0.0
# define CENTER_IM_JULIA 0.0
# define RE_RANGE_JULIA 4.0

# define CENTER_RE_BURNINGSHIP -1.7
# define CENTER_IM_BURNINGSHIP 0.03
# define RE_RANGE_BURNINGSHIP 0.3

typedef struct s_region
{
	int	start_x;
	int	start_y;
	int	end_x;
	int	end_y;
}	t_region;

typedef struct s_complex
{
	double	re;
	double	im;
}	t_complex;

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
	int			fractal_type;
	int			color_scheme;
	int			max_iter;
	double		zoom;
	t_complex	c_julia;
	t_complex	center;
	double		re_range;
}	t_fractal;

typedef struct s_app_state
{
	void		*mlx;
	void		*win;
	t_img		image;
	t_fractal	fractal;
}	t_app_state;

void		ft_strtolower(char *str);
int			ft_strcmp(const char *s1, const char *s2);
void		ft_putstr_fd(char *s, int fd);
double		ft_atod(const char *str);
void		init_window(char *title, t_app_state *state);
void		init_fractal(char **input, t_app_state *state);
void		set_fractal_range(t_app_state *state);
void		draw_fractal(t_app_state *state, t_region region);
t_complex	pixel_to_complex(const t_app_state *state, int x, int y);
int			get_color(t_app_state *state, size_t iteration);
size_t		mandelbrot(t_complex c);
size_t		julia(t_complex z, t_complex c);
size_t		burningship(t_complex c);
t_complex	c_mul(t_complex a, t_complex b);
t_complex	c_add(t_complex a, t_complex b);
int			key_event(int key, t_app_state *state);
int			mouse_event(int key, int x, int y, t_app_state *state);
void		*ft_memmove(void *dest, const void *src, size_t len);
void		handle_panning(int key, t_app_state *state);
t_region	set_region(int x_min, int x_max, int y_min, int y_max);
void		change_color(t_app_state *state);
void		reset_coord(t_app_state *state);
void		zoom_on_mouse(t_app_state *env, int mouse_x,
				int mouse_y, double zoom_factor);
int			destroy_event(t_app_state *state, int exit_status);
void		shift_image(t_app_state *state, int shift_x, int shift_y);
void		change_center(t_app_state *state, int mouse_x, int mouse_y);
void		ft_bzero(void *s, size_t n);
int			destroy_event_wrapper(t_app_state *state);

#endif
