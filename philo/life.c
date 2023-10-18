/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   life.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdogan <gdogan@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:50:32 by gdogan            #+#    #+#             */
/*   Updated: 2022/04/19 15:50:36 by gdogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	locker(t_philo *p, int rank)
{
	pthread_mutex_lock(&p->mutexes[rank]);
	print(p, "has taken a fork\n", gettime(&p->start), rank + 1);
	pthread_mutex_lock(&p->mutexes[(rank + 1) % p->count]);
	print(p, "has taken a fork\n", gettime(&p->start), rank + 1);
}

void	unlocker(t_philo *p, int rank)
{
	pthread_mutex_unlock(&p->mutexes[(rank + 1) % p->count]);
	pthread_mutex_unlock(&p->mutexes[rank]);
}

void	philo_eat(t_philo *p, int rank)
{
	long long	s;

	s = gettime(&p->start);
	pthread_mutex_lock(&p->rook);
	p->last_eat[rank] = s;
	print(p, "is eating\n", s, rank + 1);
	if (++p->eaten[rank] == p->eat_count)
		p->eaten_count--;
	pthread_mutex_unlock(&p->rook);
	smart_sleep(p, p->eat_time);
}

void	philo_sleep(t_philo *p, int rank)
{
	print(p, "is sleeping\n", gettime(&p->start), rank + 1);
	smart_sleep(p, p->sleep_time);
}

void	*philo(void *args)
{
	t_philo	*philos;
	int		rank;

	rank = ((t_arg *)args)->rank;
	philos = ((t_arg *)args)->philos;
	if (rank % 2)
		usleep(15000);
	while (1)
	{
		locker(philos, rank);
		philo_eat(philos, rank);
		unlocker(philos, rank);
		philo_sleep(philos, rank);
		print(philos, "is thinking\n", gettime(&philos->start), rank + 1);
		usleep(1000);
	}
	return (NULL);
}
