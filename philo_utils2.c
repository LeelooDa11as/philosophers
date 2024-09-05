/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:11:09 by kkoval            #+#    #+#             */
/*   Updated: 2024/09/05 16:27:29 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	assign_table(t_table *table, int ac, char *av[])
{
	table->philo_num = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	if (table->time_to_die < table->time_to_eat)
		table->time_to_eat = table->time_to_die +1;
	table->time_to_sleep = ft_atoi(av[4]);
	if (table->time_to_die < table->time_to_sleep)
		table->time_to_sleep = table->time_to_die + 1;
	table->n_time_to_eat = -1;
	if (ac == 6)
		table->n_time_to_eat = ft_atoi(av[5]);
	table->n_philos_ate = 0;
	table->finish_game = 0;
}

int	failed_create(t_table *table, t_philo *philos, int i)
{
	set_finish_mutex(table, 1);
	pthread_mutex_unlock(&table->start_life);
	while (--i >= 0)
		pthread_join(philos[i].thread, NULL);
	write(2, "failed create\n", 14);
	return (1);
}

int	get_finish_mutex(t_table *table)
{
	int	finish;

	pthread_mutex_lock(&table->mutex_finish);
	finish = table->finish_game;
	pthread_mutex_unlock(&table->mutex_finish);
	return (finish);
}

void	set_finish_mutex(t_table *table, int i)
{
	pthread_mutex_lock(&table->mutex_finish);
	table->finish_game = i;
	pthread_mutex_unlock(&table->mutex_finish);
}
