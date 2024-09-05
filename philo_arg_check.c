/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_arg_check.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 15:51:34 by kkoval            #+#    #+#             */
/*   Updated: 2024/09/05 16:27:55 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_numeric(char *str)
{
	if (!str || *str == '\0')
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	long	res;
	int		sig;

	res = 0;
	sig = 1;
	if (*str == '-')
		sig = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
		if (res > __INT_MAX__)
			return (0);
	}
	return (res * sig);
}

int	check_args(int ac, char *args[])
{
	int	x;

	x = 1;
	while (x < ac)
	{
		if (is_numeric(args[x]) == 0)
			return (-1);
		if (ft_atoi(args[x]) <= 0)
			return (-1);
		x++;
	}
	return (1);
}
