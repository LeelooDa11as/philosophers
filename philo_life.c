/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 20:43:02 by kate              #+#    #+#             */
/*   Updated: 2024/08/30 17:40:32 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		philo_eat(t_philo *philo)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	first_fork = philo->left_fork;
	second_fork = philo->right_fork;
	if (philo->id == philo->table->philo_num)
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}

	pthread_mutex_lock(first_fork);
	philo_status(philo, "has taken a fork");
	pthread_mutex_lock(second_fork);
	philo_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->table->mutex_philo_ate);
	philo->last_meal = get_game_time_ms(philo->table);
	pthread_mutex_unlock(&philo->table->mutex_philo_ate);
	philo_status(philo, "is eating");
	ft_sleep(philo->table->time_to_eat);
	pthread_mutex_unlock(second_fork);
	pthread_mutex_unlock(first_fork);
	pthread_mutex_lock(&philo->table->mutex_philo_ate);
	philo->times_to_eat--;
	if (philo->times_to_eat == 0)
		philo->table->n_philos_ate++;
	pthread_mutex_unlock(&philo->table->mutex_philo_ate);
	philo_status(philo, "is sleeping");
	ft_sleep(philo->table->time_to_sleep);
	philo_status(philo, "is thinking");
}

void	*game_master(void *t)
{
	t_table	*table;
	t_philo	philo;
	int		i;
	int 	finish;

	table = (t_table*) t;
	i = 0;
	finish = get_finish_mutex(table);
	while (finish == 0)
	{	
		i = 0;
		philo = table->philos[i];
		
		if (get_game_time_ms(philo.table) - philo.last_meal > table->time_to_die)
		{	
			philo_status(&philo, " died");
			set_finish_mutex(table, 1);
		}
		if (++i == table->philo_num)
		
		pthread_mutex_lock(&table->mutex_philo_ate);
		if (table->n_philos_ate == table->philo_num)
			set_finish_mutex(table, 1);
		pthread_mutex_unlock(&table->mutex_philo_ate);
		ft_sleep(1);
		finish = get_finish_mutex(table);
	}
	return ((void *)0);
}

void	*philo_life(void *p)
{
	t_philo	*philo;
	int 	finish;
	
	philo = (t_philo *) p;
	pthread_mutex_lock(&philo->table->start_life);
	pthread_mutex_unlock(&philo->table->start_life);
	if (philo->id%2 == 1)
		ft_sleep(1);
	finish = get_finish_mutex(philo->table);
	while (finish == 0)
	{
		if (philo->table->philo_num > 1)
			philo_eat(philo);
		else
		{
			pthread_mutex_lock(philo->left_fork);
			philo_status(philo, "has taken a fork");
			pthread_mutex_unlock(philo->left_fork);
			ft_sleep(philo->table->time_to_die + 10);
		}
		finish = get_finish_mutex(philo->table);
	}
	return ((void *)0);
}