/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kkoval <kkoval@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 16:15:38 by kate              #+#    #+#             */
/*   Updated: 2024/09/05 16:26:11 by kkoval           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_sleep(int ms)
{
	int	time;

	time = get_time_ms();
	while (get_time_ms() - time < ms)
		usleep(200);
	return (0);
}

void	philo_status(t_philo *philo, char *msg)
{
	int	time;
	int	finish;

	pthread_mutex_lock(&(philo->table->print_mutex));
	time = get_time_ms() - philo->table->start_time;
	finish = get_finish_mutex(philo->table);
	if (finish == 0)
		printf("%d %d %s\n", time, philo->id, msg);
	pthread_mutex_unlock(&(philo->table->print_mutex));
}

// it returns current time in miliseconds
int	get_time_ms(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	get_game_time_ms(t_table *table)
{
	return (get_time_ms() - table->start_time);
}
