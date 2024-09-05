/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:02:40 by kate              #+#    #+#             */
/*   Updated: 2024/09/05 16:22:50 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_philos(t_philo *philos, t_table *table)
{
	int	i;
	int	n;

	i = -1;
	n = table->philo_num;
	while (++i < n)
	{
		philos[i].id = i + 1;
		philos[i].last_meal = 0;
		philos[i].times_to_eat = table->n_time_to_eat;
		philos[i].table = table;
		philos[i].left_fork = &table->forks[i];
		if (i == 0)
			philos[i].right_fork = &table->forks[n - 1];
		else
			philos[i].right_fork = &table->forks[i - 1];
		if (pthread_create(&philos[i].thread, NULL, &philo_life, \
		(void *)&philos[i]) != 0)
			return (failed_create(table, philos, i));
	}
	return (0);
}

void	mutex_init(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_init(&table->print_mutex, NULL);
	pthread_mutex_init(&table->start_life, NULL);
	pthread_mutex_init(&table->mutex_philo_ate, NULL);
	pthread_mutex_init(&table->mutex_finish, NULL);
	while (i < table->philo_num)
	{
		pthread_mutex_init(&table->forks[i], NULL);
		i++;
	}
}

void	mutex_destroy(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->start_life);
	pthread_mutex_destroy(&table->mutex_philo_ate);
	pthread_mutex_destroy(&table->mutex_finish);
}

int	init_table(t_table *table, int ac, char *av[])
{
	assign_table(table, ac, av);
	table->philos = malloc(sizeof(t_philo) * table->philo_num);
	if (!(table->philos))
		return (-1);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_num);
	if (!table->forks)
		return (ft_free_philos(table));
	mutex_init(table);
	pthread_mutex_lock(&table->start_life);
	if (init_philos(table->philos, table))
		return (-1);
	ft_sleep(100);
	table->start_time = get_time_ms();
	pthread_create(&table->game_master_thread, NULL, &game_master, \
	(void *)table);
	pthread_mutex_unlock(&table->start_life);
	return (1);
}

int	main(int ac, char *av[])
{
	t_table	table;
	int		n;

	n = 0;
	if (ac < 5 || ac > 6 || check_args(ac, av) == -1)
	{
		write(2, "The arguments introduced are not correct, try again\n", 52);
		return (1);
	}
	if (init_table(&table, ac, av) == -1)
	{
		ft_free(&table);
		mutex_destroy(&table);
		return (1);
	}
	while (n < table.philo_num)
	{
		pthread_join(table.philos[n].thread, NULL);
		n++;
	}
	pthread_join(table.game_master_thread, NULL);
	ft_free(&table);
	mutex_destroy(&table);
	return (0);
}
