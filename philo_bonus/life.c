/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdogan <gdogan@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:55:53 by gdogan            #+#    #+#             */
/*   Updated: 2022/04/19 15:55:56 by gdogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	smart_sleep(t_philo *p, long long ms)
{
	long long	begin;

	begin = gettime(&p->start);
	while (gettime(&p->start) - begin < ms)
		usleep(1000);
}

void	philo_eat(t_philo *p, int rank)
{
	long long	s;

	s = gettime(&p->start);
	print("is eating\n", s, rank + 1, p);
	sem_wait(p->rook);
	if (++p->eaten == p->eat_count)
		sem_post(p->life);
	p->last_eat = s;
	sem_post(p->rook);
	smart_sleep(p, p->eat_time);
}

void	philo_sleep(t_philo *p, int rank)
{
	print("is sleeping\n", gettime(&p->start), rank + 1, p);
	smart_sleep(p, p->sleep_time);
}

void	*philo_dying(void *arg)
{
	t_philo		*philos;
	long long	time_passed;

	philos = (t_philo *)arg;
	while (1)
	{
		time_passed = gettime(&philos->start);
		sem_wait(philos->rook);
		if (time_passed - philos->last_eat >= philos->die_time)
		{
			sem_wait(philos->msg);
			printf("%lld %d died\n", time_passed, philos->rank + 1);
			sem_post(philos->kill);
			exit(0);
		}
		sem_post(philos->rook);
	}
	exit(0);
}

void	*philo(t_philo *philos, int rank)
{
	pthread_t	death;

	philos->msg = sem_open("/msg", 0);
	philos->life = sem_open("/life", 0);
	philos->kill = sem_open("/kill", 0);
	philos->mutex = sem_open("/mutex", 0);
	sem_wait(philos->kill);
	sem_wait(philos->life);
	philos->rank = rank;
	pthread_create(&death, NULL, philo_dying, philos);
	if (rank % 2)
		usleep(15000);
	while (1)
	{
		locker(philos, rank);
		philo_eat(philos, rank);
		unlocker(philos);
		philo_sleep(philos, rank);
		print("is thinking\n", gettime(&philos->start), rank + 1, philos);
		usleep(1000);
	}
	exit(0);
}
