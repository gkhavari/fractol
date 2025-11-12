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

int	main(int argc, char **argv)
{
	t_app_state	state;
	t_region	full_region;

	if (argc > 1)
		ft_strtolower(argv[1]);
	input_info(argc, argv);
	init_window(argv[1], &state);
	init_fractal(argv + 1, &state);
	full_region = set_region(0, WIDTH, 0, HEIGHT);
	draw_fractal(&state, full_region);
	mlx_key_hook(state.win, key_event, &state);
	mlx_mouse_hook(state.win, mouse_event, &state);
	mlx_hook(state.win, 17, 0, destroy_event_wrapper, &state);
	mlx_loop(state.mlx);
	return (0);
}
