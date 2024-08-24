/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kate <kate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:14:22 by kate              #+#    #+#             */
/*   Updated: 2024/08/24 21:03:46 by kate             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_table t_table;
typedef struct	s_philo
{
	int			id;
	int			fork;
	int			last_meal;
	int			times_ate;
	pthread_t	thread;
	t_table		*table;
}				t_philo;

typedef struct s_table
{
	int				philo_num;
	t_philo			*philos;
	pthread_mutex_t	forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_time_to_eat;
	pthread_mutex_t	print_mutex;
	int				start_time;

}				t_table;

//				PHILO_UTILS
int		check_args(int ac, char *args[]);
int		ft_atoi(const char *str);
int		get_time_ms(void);
void	philo_status(t_philo *philo, char *msg);
int		ft_sleep(int ms);

#endif