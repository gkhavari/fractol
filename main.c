#include "fractol.h"

static int	check_input(int argc, char **argv)
{
	if (argc == 2 && ft_strcmp(argv[1], "mandelbrot") == 0)
		return (0);
	/*if (argc == 4 && ft_strcmp(argv[1], "julia") == 0)
	{
		if (is_valid_julia_arg(argv[2]) && is_valid_julia_arg(argv[3]))
			return (0);
		else
			return (1);
	}
	if (argc == 2 && ft_strcmp(argv[1], "burningship") == 0)
		return (0);*/
	return (1);
}

static void input_info(int argc, char **argv)
{
	if (argc == 3 && ft_strcmp(argv[1], "julia") == 0 && ft_strcmp(argv[2], "help") == 0 )
	{
		ft_putstr_fd("Interesting parameters for Julia:\n", 1);
		ft_putstr_fd("−0.8 + 0.156i\n", 1);
		ft_putstr_fd("−0.4 + 0.6i\n", 1);
		ft_putstr_fd("0.285 + 0\n", 1);
		exit(EXIT_SUCCESS);
	}
	if (check_input(argc, argv))
	{
        ft_putstr_fd("Usage:\n", 2);
        ft_putstr_fd("  ./fractol mandelbrot\n", 2);
        ft_putstr_fd("  ./fractol julia <real> <imag> (range -2 to 2)\n", 2);
        ft_putstr_fd("  ./fractol burningship\n", 2);
        ft_putstr_fd("  ./fractol tricorn\n", 2);
		exit(EXIT_SUCCESS);
    }
}

int	main(int argc, char **argv)
{
	t_app_state app_state;
	char **input;

	input_info(argc, argv);
	input = &argv[1];
	init_window(*input, &app_state);
	init_fractal(input, &app_state);
	app_state.fractal.draw;
	mlx_put_image_to_window(app_state.mlx, app_state.win, app_state.image.img, 0, 0);

//	mlx_key_hook(app_state.win, key_event, &engine);
//	mlx_mouse_hook(app_state.win, mouse_event, &engine);
//	mlx_hook(app_state.win, 6, 1L << 6, mousemove_event, &engine);
	mlx_hook(app_state.win, 17, 0, destroy_event, &app_state);
	mlx_loop(app_state.mlx);
	return (0);
}