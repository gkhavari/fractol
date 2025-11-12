/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gkhavari <gkhavari@student.42vienna.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:36:09 by gkhavari          #+#    #+#             */
/*   Updated: 2025/11/05 17:36:14 by gkhavari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	c_add(t_complex a, t_complex b)
{
	t_complex	res;

	res.re = a.re + b.re;
	res.im = a.im + b.im;
	return (res);
}

t_complex	c_mul(t_complex a, t_complex b)
{
	t_complex	res;

	res.re = a.re * b.re - a.im * b.im;
	res.im = a.re * b.im + a.im * b.re;
	return (res);
}

void	ft_strtolower(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] = str[i] + ('a' - 'A');
		i++;
	}
	str[i] = '\0';
}

int	is_valid_julia_arg(char *str)
{
	size_t	i;
	size_t	dot_count;
	double	val;

	i = 0;
	dot_count = 0;
	if (!str || str[0] == '\0')
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (str[i] == '\0')
		return (0);
	while (ft_isdigit(str[i]) || str[i] == '.')
	{
		if (str[i] == '.')
			dot_count++;
		i++;
	}
	if (dot_count > 1)
		return (0);
	if (str[i] != '\0' || str[i - 1] == '.')
		return (0);
	val = ft_atof(str);
	return (!isinf(val) && val >= -2.0 && val <= 2.0);
}
