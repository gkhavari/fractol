#include  "fractol.h"

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

static void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= 1920 || y < 0 || y >= 1080)
		return;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

static void	draw_circle(t_img *img, int cx, int cy, int radius, int color)
{
	for (int y = -radius; y <= radius; y++)
	{
		for (int x = -radius; x <= radius; x++)
		{
			if (x * x + y * y <= radius * radius)
				my_mlx_pixel_put(img, cx + x, cy + y, color);
		}
	}
}

int main(void)
{
    void    *mlx;
    void    *mlx_win;
    t_img   mlx_img;

    mlx = mlx_init();
    if (!mlx)
        return (1);
    mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello World");
    if (!mlx_win)
        return (1);
    mlx_img.img = mlx_new_image(mlx, 1920, 1080);
    if (!mlx_img.img)
        return (1);
   	mlx_img.addr = mlx_get_data_addr(mlx_img.img, &mlx_img.bits_per_pixel,
		&mlx_img.line_length, &mlx_img.endian);
    draw_circle(&mlx_img, 1920 / 2, 1080 / 2, 200, 0x00FFFFFF);
    mlx_put_image_to_window(mlx, mlx_win, mlx_img.img, 0, 0);
    mlx_loop(mlx);
    return (0);
}