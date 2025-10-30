#include "fractol.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;
    int bytes_written;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		bytes_written = write(fd, &s[i], 1);
        if (bytes_written == -1)
            return ;
		i++;
	}
}

t_complex c_add(t_complex a, t_complex b)
{
    t_complex res = {a.re + b.re, a.im + b.im};
    return (res);
}

t_complex c_mul(t_complex a, t_complex b)
{
    t_complex res = {a.re * b.re - a.im * b.im,
                     a.re * b.im + a.im * b.re};
    return (res);
}

double	ft_atof(const char *str)
{
    int i = 0;
    int sign = 1;
    double result = 0.0;
    double frac = 0.0;
    double divisor = 10.0;

    if (str[i] == '-' || str[i] == '+')
    {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10.0 + (str[i] - '0');
        i++;
    }
    if (str[i] == '.')
    {
        i++;
        while (str[i] >= '0' && str[i] <= '9')
        {
            frac += (str[i] - '0') / divisor;
            divisor *= 10.0;
            i++;
        }
    }
   return sign * (result + frac);
}

int ft_strcmp(const char *s1, const char *s2)
{
    int i = 0;

    while (s1[i] && s2[i])
    {
        if (s1[i] != s2[i])
            return ((unsigned char)s1[i] - (unsigned char)s2[i]);
        i++;
    }
    return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}