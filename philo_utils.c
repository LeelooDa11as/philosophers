/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:15:38 by kate              #+#    #+#             */
/*   Updated: 2024/08/29 19:23:20 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		ft_sleep(int ms)
{
	int	time;

	time = get_time_ms();
	while (get_time_ms() - time < ms)
		usleep(500);
	return (0);
}

void	philo_status(t_philo *philo, char *msg)
{
	int		time;
	
	pthread_mutex_lock(&(philo->table->print_mutex));
	time = get_time_ms() - philo->table->start_time;
	pthread_mutex_lock(&(philo->table->mutex_finish));
	if (philo->table->finish_game == 0)
		printf("%d %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&(philo->table->mutex_finish));
	pthread_mutex_unlock(&(philo->table->print_mutex));

}

// it returns current time in miliseconds
int get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	get_game_time_ms(t_table *table)
{
	return (get_time_ms() - table->start_time);
}

int	is_numeric(char *str)
{
	if (!str || *str == '\0')
		return (0);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	int	res;
	int	sig;

	res = 0;
	sig = 1;
	if (*str == '-')
		sig = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		str++;
	}
	return (res * sig);
}

int	check_args(int ac, char *args[])
{
	int	x;

	x = 1;
	while (x < ac)
	{
		if (is_numeric(args[x]) == 0)
			return (-1);
		if (ft_atoi(args[x]) <= 0)
			return (-1);
		x++;
	}
	return (1);
}

int 	get_finish_mutex(t_table *table)
{		
	int finish;

	pthread_mutex_lock(&table->mutex_finish);
	finish = table->finish_game;
	pthread_mutex_unlock(&table->mutex_finish);
	return (finish);
}

void 	set_finish_mutex(t_table *table, int i)
{		

	pthread_mutex_lock(&table->mutex_finish);
	table->finish_game = i;
	pthread_mutex_unlock(&table->mutex_finish);
}