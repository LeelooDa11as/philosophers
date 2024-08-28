/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:02:40 by kate              #+#    #+#             */
/*   Updated: 2024/08/28 19:04:36 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_philo *philos, t_table *table)
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
		pthread_create(&philos[i].thread, NULL, &philo_life, (void *)&philos[i]);
	}
}

void	mutex_init(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_init(&table->print_mutex, NULL);
	pthread_mutex_init(&table->start_life, NULL);
	pthread_mutex_init(&table->mutex_philo_ate, NULL);
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
}

int	init_table(t_table *table, int ac, char *av[])
{
	table->philo_num = ft_atoi(av[1]);
	table->time_to_die = ft_atoi(av[2]);
	table->time_to_eat = ft_atoi(av[3]);
	table->time_to_sleep = ft_atoi(av[4]);
	table->n_time_to_eat = -1;
	if (ac == 6)
		table->n_time_to_eat = ft_atoi(av[5]);
	table->n_philos_ate = 0;
	table->philos = malloc(sizeof(t_philo) * table->philo_num);
	if (!(table->philos))
		return (-1);
	table->finish_game = 0;
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_num);
	if (!table->forks)
		return (ft_free_philos(table));
	mutex_init(table);
	pthread_mutex_lock(&table->start_life);
	init_philos(table->philos, table);
	ft_sleep(50);
	table->start_time = get_time_ms();
	pthread_create(&table->game_master_thread, NULL, &game_master, (void *)table);
	pthread_mutex_unlock(&table->start_life);
	return (1);
}

int main(int ac, char *av[])
{
	t_table	table;
	int		n;
	
	n = 0;
	if (ac < 5 || ac > 6 || check_args(ac, av) == -1)
	{
		printf("The arguments introduced are not correct, try again\n");
		return (1);
	}
	if (init_table(&table, ac, av) == -1)
		return (1);
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
