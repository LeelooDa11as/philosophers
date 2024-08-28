/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kate <kate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:43:02 by kate              #+#    #+#             */
/*   Updated: 2024/08/28 15:09:35 by kate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	philo_status(philo, "has taken a fork");
	philo_status(philo, "has taken a fork");
	philo_status(philo, "is eating");
	//philo->last_meal = get_game_time_ms(philo->table);
	ft_sleep(philo->table->time_to_eat);
	philo->last_meal = get_game_time_ms(philo->table);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	philo->times_to_eat--;
}

void	*game_master(void *t)
{
	t_table	*table;
	t_philo	philo;
	int		i;

	table = (t_table*) t;
	i = 0;
	while (table->finish_game == 0)
	{
		philo = table->philos[i];
		if (get_game_time_ms(philo.table) - philo.last_meal > table->time_to_die)
		{	
			philo_status(&philo, "is dead");
			table->finish_game = 1;
		}
		i++;
		if (i == table->philo_num)
			i = 0;
		//pthread_mutex_lock(&table->mutex_philo_ate); not sure if necessary
		if (table->n_philos_ate == table->philo_num)
			table->finish_game = 1;
		//pthread_mutex_unlock(&table->mutex_philo_ate); same same
		ft_sleep(1);

	}
	return ((void *)0);
}

void	*philo_life(void *p)
{
	t_philo	*philo;
	
	philo = (t_philo *) p;
	printf("philosppher num %d is brought to life\n", philo->id);
	pthread_mutex_lock(&philo->table->start_life);
	pthread_mutex_unlock(&philo->table->start_life);
	if (philo->id%2 == 1)
		ft_sleep(1);
	while (philo->table->finish_game == 0)
	{
		if (philo->table->philo_num > 1){
			philo_eat(philo);
			philo_status(philo, "is sleeping");
			ft_sleep(philo->table->time_to_sleep);
			philo_status(philo, "is thinking");
		}
		if (philo->times_to_eat == 0)
		{
			pthread_mutex_lock(&philo->table->mutex_philo_ate);
			philo->table->n_philos_ate++;
			pthread_mutex_unlock(&philo->table->mutex_philo_ate);
		}
	}
	return ((void *)0);
}