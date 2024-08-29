/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:11:09 by kkoval            #+#    #+#             */
/*   Updated: 2024/08/29 14:52:07 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_free_philos(t_table *table)
{
	free(table->philos);
	return (-1);
}

void	ft_free(t_table *table)
{
	free(table->forks);
	ft_free_philos(table);
}
