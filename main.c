/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:27:49 by gkhavari          #+#    #+#             */
/*   Updated: 2025/11/05 17:27:52 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	is_valid_julia_arg(char *str)
{
	size_t	i;
	size_t	dot_count;

	i = 0;
	dot_count = 0;
	if (!str || str[0] == '\0')
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while ((str[i] <= '9' && str[i] >= '0') || str[i] == '.')
	{
		if (str[i] == '.')
			dot_count = dot_count + 1;
		i++;
	}
	if (dot_count > 1)
		return (0);
	if (str[i] != '\0')
		return (0);
	if (ft_atof(str) < -2.0 || ft_atof(str) > 2.0)
		return (0);
	return (1);
}

static int	check_input(int argc, char **argv)
{
	if (argc == 2 && ft_strcmp(argv[1], "mandelbrot") == 0)
		return (0);
	if (argc == 4 && ft_strcmp(argv[1], "julia") == 0)
	{
		if (is_valid_julia_arg(argv[2]) && is_valid_julia_arg(argv[3]))
			return (0);
		else
			return (1);
	}
	if (argc == 2 && ft_strcmp(argv[1], "burningship") == 0)
		return (0);
	return (1);
}

static void	input_info(int argc, char **argv)
{
	if (argc == 3 && ft_strcmp(argv[1], "julia") == 0
		&& ft_strcmp(argv[2], "help") == 0)
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
		ft_putstr_fd("  ./fractol julia <real> <imag> (range -2 to 2)\n",
			2);
		ft_putstr_fd("  ./fractol burningship\n", 2);
		ft_putstr_fd("  ./fractol tricorn\n", 2);
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char **argv)
{
	t_app_state	state;
	char		**input;
	
	if (argc == 1)
		input_info(argc, argv);
	ft_strtolower(argv[1]);
	input_info(argc, argv);
	input = &argv[1];
	init_window(*input, &state);
	init_fractal(input, &state);
	draw_fractal(&state, FULL_REGION);
	mlx_key_hook(state.win, key_event, &state);
	mlx_mouse_hook(state.win, mouse_event, &state);
	mlx_hook(state.win, 17, 0, destroy_event, &state);
	mlx_loop(state.mlx);
	return (0);
}
