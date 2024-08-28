/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:11:09 by kkoval            #+#    #+#             */
/*   Updated: 2024/08/28 19:05:37 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		ft_free_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		free(&table->philos[i]);
		i++;
	}
	return (-1);
}

void    ft_free(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		free(&table->forks[i]);
		i++;
	}
	ft_free_philos(table);
}
