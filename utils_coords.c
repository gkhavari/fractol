/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_coords.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:18:34 by gkhavari          #+#    #+#             */
/*   Updated: 2025/11/08 17:18:36 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_region	set_region(x_min, x_max, y_min, y_max)
{
	t_region	region;

	region.start_x = x_min;
	region.end_x = x_max;
	region.start_y = y_min;
	region.end_y = y_max;
	return (region);
}
