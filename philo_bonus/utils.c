/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdogan <gdogan@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:55:39 by gdogan            #+#    #+#             */
/*   Updated: 2022/04/19 15:55:41 by gdogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	ft_atoi(char *str)
{
	int		i;
	long	res;

	res = 0;
	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i++] - '0';
		if (res > 2147483647)
			return (2147483648);
	}
	return (res);
}

long long	gettime(struct timeval *s)
{
	struct timeval	e;
	long long		s_ms;
	long long		e_ms;

	gettimeofday(&e, NULL);
	s_ms = s->tv_sec * 1000LL + s->tv_usec / 1000;
	e_ms = e.tv_sec * 1000LL + e.tv_usec / 1000;
	return (e_ms - s_ms);
}

void	print(char *str, long long time, int rank, t_philo *philo)
{
	sem_wait(philo->msg);
	printf("%lld %d %s", time, rank, str);
	sem_post(philo->msg);
}

void	locker(t_philo *p, int rank)
{
	sem_wait(p->mutex);
	print("has taken a fork\n", gettime(&p->start), rank + 1, p);
	sem_wait(p->mutex);
	print("has taken a fork\n", gettime(&p->start), rank + 1, p);
}

void	unlocker(t_philo *p)
{
	sem_post(p->mutex);
	sem_post(p->mutex);
}
