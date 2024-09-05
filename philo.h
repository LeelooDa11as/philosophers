/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kate <kate@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/24 17:14:22 by kate              #+#    #+#             */
/*   Updated: 2024/09/05 00:25:05 by kate             ###   ########.fr       */
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
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				last_meal;
	int				times_to_eat;
	pthread_t		thread;
	t_table			*table;
}				t_philo;

typedef struct s_table
{
	int				philo_num;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_time_to_eat;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	start_life;
	int				finish_game;
	int				start_time;
	pthread_mutex_t	mutex_philo_ate;
	pthread_mutex_t	mutex_finish;
	pthread_t		game_master_thread;
	int				n_philos_ate;

}				t_table;

//				PHILO LIFE
void	*game_master(void *t);
void	*philo_life(void *p);

//				PHILO_UTILS
int		check_args(int ac, char *args[]);
int		ft_atoi(const char *str);
int 	get_time_ms(void);
int		get_game_time_ms(t_table *table);
void	philo_status(t_philo *philo, char *msg);
int		ft_sleep(int ms);
int 	get_finish_mutex(t_table *table);
void 	set_finish_mutex(t_table *table, int i);

//				PHILO_UTILS2



//				PHILO_FREE
int		ft_free_philos(t_table *table);
void    ft_free(t_table *table);

#endif