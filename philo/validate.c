/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naharagu <naharagu@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/17 15:14:51 by naharagu          #+#    #+#             */
/*   Updated: 2023/01/17 21:17:19 by naharagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sopher.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

bool	is_less_than_maxint(const char *str)
{
	int			len;
	long long	tmp;

	len = 0;
	while (str[len])
	{
		len++;
		if (len > 10)
			return (false);
	}
	len = 0;
	tmp = 0;
	while (str[len])
	{
		tmp = tmp * 10 + (str[len] - '0');
		len++;
	}
	if (tmp > INT_MAX)
		return (false);
	return (true);
}

int	ft_atoi(const char *str)
{
	int			sign;
	long long	res;

	sign = 1;
	res = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while (ft_isdigit(*str))
	{
		if (sign == 1 && (res > ((LONG_MAX - (*str - '0')) * sign) / 10))
			return ((int)LONG_MAX);
		else if (sign == -1 && (res < ((LONG_MIN - (*str - '0')) * sign) / 10))
			return ((int)LONG_MIN);
		res = res * 10 + ((*str++ - '0') * sign);
	}
	return (res);
}

int	validate_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc != 5 && argc != 6)
		return (-1);
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
			if (!ft_isdigit(argv[i][j++]))
				return (-1);
		i++;
	}
	i = 1;
	while (i < argc)
	{
		if (!is_less_than_maxint(argv[i]))
			return (-1);
		if (ft_atoi(argv[i++]) <= 0)
			return (-1);
	}
	return (0);
}
