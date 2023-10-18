/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdogan <gdogan@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:51:48 by gdogan            #+#    #+#             */
/*   Updated: 2022/04/19 15:51:49 by gdogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	print(t_philo *philos, char *str, long long time, int rank)
{
	pthread_mutex_lock(&philos->msg);
	printf("%lld %d %s", time, rank, str);
	pthread_mutex_unlock(&philos->msg);
}

void	death_control(t_philo *philos)
{
	long long	time_passed;
	int			i;

	while (1)
	{
		i = -1;
		while (++i < philos->count)
		{
			pthread_mutex_lock(&philos->rook);
			time_passed = gettime(&philos->start) - philos->last_eat[i];
			if (time_passed >= philos->die_time)
			{
				pthread_mutex_lock(&philos->msg);
				time_passed = gettime(&philos->start);
				printf("%lld %d died\n", time_passed, i + 1);
				exit(0);
			}
			pthread_mutex_unlock(&philos->rook);
		}
	}
}
