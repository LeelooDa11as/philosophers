/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kate <kate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:43:02 by kate              #+#    #+#             */
/*   Updated: 2024/08/25 21:33:58 by kate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_life(void *p)
{
	t_philo	*philo;
	int		meals;
	
	philo = (t_philo *) p;
	meals = philo->table->n_time_to_eat;
	printf("philosppher num %d is brought to life\n", philo->id);
	pthread_mutex_lock(&philo->table->start_life);
	pthread_mutex_unlock(&philo->table->start_life);
	while (philo->times_ate <= meals)
	{
		philo_status(philo, "is eating");
		ft_sleep(philo->table->time_to_eat);
		philo_status(philo, "is sleeping");
		ft_sleep(philo->table->time_to_sleep);
		philo_status(philo, "is thinking");
		philo->times_ate++;
	}
	return ((void *)0);
}