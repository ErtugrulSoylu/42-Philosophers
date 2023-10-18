/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdogan <gdogan@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:55:23 by gdogan            #+#    #+#             */
/*   Updated: 2022/04/19 15:55:25 by gdogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdbool.h>
# include <sys/time.h>
# include <unistd.h>
# include <time.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <signal.h>

typedef struct s_philo
{
	long long		die_time;
	long long		eat_time;
	long long		sleep_time;
	long long		last_eat;
	int				count;
	int				eat_count;
	int				eaten;
	int				rank;
	sem_t			*mutex;
	sem_t			*msg;
	sem_t			*life;
	sem_t			*kill;
	sem_t			*rook;
	pid_t			*id;
	struct timeval	start;
}	t_philo;

int			is_valid(char *str);
int			invalid_arg(int argc, char **argv);
long		ft_atoi(char *str);
void		run_processes(t_philo *philos);
void		philo_init(t_philo *philos, char **argv, int argc);
void		*philo(t_philo *philos, int rank);
long long	gettime(struct timeval *s);
void		print(char *str, long long time, int rank, t_philo *philo);
void		locker(t_philo *p, int rank);
void		unlocker(t_philo *p);
void		*philo_dying(void *arg);
void		kill_processes(t_philo *philos);
void		*death_control(t_philo *philos);
void		*eat_control(void *arg);
void		philo_init(t_philo *philos, char **argv, int argc);
void		run_processes(t_philo *philos);
void		smart_sleep(t_philo *p, long long ms);

#endif
