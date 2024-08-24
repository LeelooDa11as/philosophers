/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kate <kate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:02:40 by kate              #+#    #+#             */
/*   Updated: 2024/08/24 21:02:55 by kate             ###   ########.fr       */
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
	init_philos(table->philos, table);
	table->start_time = get_time_ms();
	pthread_mutex_init(&table->print_mutex, NULL);
	return (1);
}

int main(int ac, char *av[])
{
	t_table	table;

	if (ac < 5 || ac > 6 || check_args(ac, av) == -1)
	{
		printf("The arguments introduced are not correct, try again\n");
		return (1);
	}
	init_table(&table, ac, av);
	ft_sleep(500);
	philo_status(&(table.philos[0]), "is eating");
	return (0);
}
