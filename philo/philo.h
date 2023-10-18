/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdogan <gdogan@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:51:27 by gdogan            #+#    #+#             */
/*   Updated: 2022/04/19 15:51:32 by gdogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>
# include <time.h>

typedef struct s_philo
{
	long long		die_time;
	long long		eat_time;
	long long		sleep_time;
	long long		*last_eat;
	int				count;
	int				eat_count;
	int				eaten_count;
	int				*eaten;
	pthread_mutex_t	msg;
	pthread_mutex_t	rook;
	pthread_mutex_t	*mutexes;
	pthread_t		*id;
	struct timeval	start;
}	t_philo;

typedef struct s_arg
{
	t_philo	*philos;
	int		rank;
}	t_arg;

long		ft_atoi(char *str);
int			is_valid(char *str);
int			invalid_arg(int argc, char **argv);
void		print(t_philo *philos, char *str, long long time, int rank);
void		locker(t_philo *p, int rank);
void		unlocker(t_philo *p, int rank);
void		philo_eat(t_philo *p, int rank);
void		s_philoleep(t_philo *p, int rank);
int			any(t_philo *philos);
long long	gettime(struct timeval *s);
void		print(t_philo *philos, char *str, long long time, int rank);
void		*philo(void *args);
void		run_threads(t_philo *philos);
void		philo_eat(t_philo *p, int rank);
void		philo_init(t_philo *philos, char **argv, int argc);
void		death_control(t_philo *philos);
void		smart_sleep(t_philo *p, long long ms);

#endif
