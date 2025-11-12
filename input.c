/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:07:04 by gkhavari          #+#    #+#             */
/*   Updated: 2025/11/11 15:07:06 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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

static void	print_usage(void)
{
	ft_putstr_fd("Usage:\n", 2);
	ft_putstr_fd("  ./fractol mandelbrot\n", 2);
	ft_putstr_fd("  ./fractol julia <real> <imag> (range -2 to 2)\n", 2);
	ft_putstr_fd("  ./fractol burningship\n", 2);
}

static void	print_julia_help(void)
{
	ft_putstr_fd("Interesting parameters for Julia:\n", 1);
	ft_putstr_fd("-0.8 + 0.156i\n", 1);
	ft_putstr_fd("-0.4 + 0.6i\n", 1);
	ft_putstr_fd("0.285 + 0\n", 1);
}

void	input_info(int argc, char **argv)
{
	if (argc == 3 && ft_strcmp(argv[1], "julia") == 0
		&& ft_strcmp(argv[2], "--help") == 0)
	{
		print_julia_help();
		exit(EXIT_SUCCESS);
	}
	if (check_input(argc, argv))
	{
		print_usage();
		exit(EXIT_FAILURE);
	}
}
