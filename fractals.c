/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractals.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:47:57 by gkhavari          #+#    #+#             */
/*   Updated: 2025/11/05 17:47:59 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

size_t	mandelbrot(t_complex c)
{
	t_complex	z;
	size_t		i;

	z.re = 0.0;
	z.im = 0.0;
	i = 0;
	while (i < MAX_ITER)
	{
		z = c_mul(z, z);
		z = c_add(z, c);
		if (z.re * z.re + z.im * z.im > 4)
			break ;
		i++;
	}
	return (i);
}

size_t	julia(t_complex z, t_complex c)
{
	int	i;

	i = 0;
	while (i < MAX_ITER)
	{
		z = c_add(c_mul(z, z), c);
		if (z.re * z.re + z.im * z.im > 4)
			break ;
		i++;
	}
	return (i);
}

size_t	burningship(t_complex c)
{
	t_complex	z;
	size_t		i;

	z.re = 0.0;
	z.im = 0.0;
	i = 0;
	while (i < MAX_ITER)
	{
		z.re = fabs(z.re);
		z.im = fabs(z.im);
		z = c_mul(z, z);
		z = c_add(z, c);
		if (z.re * z.re + z.im * z.im > 4)
			break ;
		i++;
	}
	return (i);
}
