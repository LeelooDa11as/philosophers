/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kate <kate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:02:40 by kate              #+#    #+#             */
/*   Updated: 2024/08/25 21:38:08 by kate             ###   ########.fr       */
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
		philos[i].times_ate = 0;
		philos[i].table = table;
		pthread_create(&philos[i].thread, NULL, &philo_life, (void *)&philos[i]);
	}
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
	table->philos = malloc(sizeof(t_philo) * table->philo_num);
	if (!(table->philos))
		return (-1);
	table->start_time = get_time_ms();
	pthread_mutex_init(&table->print_mutex, NULL);
	pthread_mutex_init(&table->start_life, NULL);
	pthread_mutex_lock(&table->start_life);
	init_philos(table->philos, table);
	ft_sleep(5000);
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
	init_table(&table, ac, av);
	while (n < table.philo_num)
	{
		pthread_join(table.philos[n].thread, NULL);
		n++;
	}
	pthread_mutex_destroy(&table.print_mutex);
	pthread_mutex_destroy(&table.start_life);
	printf("happy to print :D \n");
	return (0);
}
