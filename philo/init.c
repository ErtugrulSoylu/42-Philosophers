/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdogan <gdogan@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:50:10 by gdogan            #+#    #+#             */
/*   Updated: 2022/04/19 15:50:14 by gdogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*mutex_creator(int num)
{
	pthread_mutex_t		*mutexes;
	int					i;

	i = -1;
	mutexes = malloc(num * sizeof(pthread_mutex_t));
	while (++i < num)
		pthread_mutex_init(&mutexes[i], NULL);
	return (mutexes);
}

void	philo_init(t_philo *philos, char **argv, int argc)
{
	philos->id = (pthread_t *)malloc(philos->count * sizeof(pthread_t));
	philos->last_eat = (long long *)malloc(philos->count * sizeof(long long));
	philos->eaten = (int *)malloc(philos->count * sizeof(int));
	memset(philos->eaten, 0, philos->count * sizeof(int));
	memset(philos->last_eat, 0, philos->count * sizeof(int));
	philos->die_time = ft_atoi(argv[2]);
	philos->eat_time = ft_atoi(argv[3]);
	philos->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		philos->eat_count = ft_atoi(argv[5]);
	else
		philos->eat_count = 2147483647;
	if (philos->eat_count == 0)
		exit(printf("everybody ate!\n"));
	philos->eaten_count = philos->count;
	philos->mutexes = mutex_creator(philos->count);
	pthread_mutex_init(&philos->msg, NULL);
	pthread_mutex_init(&philos->rook, NULL);
}

void	*eat_control(void *args)
{
	t_philo	*philo;

	philo = (t_philo *)args;
	while (1)
	{
		pthread_mutex_lock(&philo->rook);
		if (philo->eaten_count == 0)
			break ;
		pthread_mutex_unlock(&philo->rook);
	}
	pthread_mutex_unlock(&philo->rook);
	pthread_mutex_lock(&philo->msg);
	printf("everybody ate!\n");
	exit(0);
	pthread_mutex_unlock(&philo->msg);
}

void	run_threads(t_philo *philos)
{
	t_arg		*args;
	pthread_t	eat;
	int			i;

	args = (t_arg *)malloc(philos->count * sizeof(t_arg));
	i = -1;
	while (++i < philos->count)
	{
		args[i].rank = i;
		args[i].philos = philos;
	}
	i = -1;
	gettimeofday(&philos->start, NULL);
	while (++i < philos->count)
	{
		pthread_create(&philos->id[i], NULL, philo, &args[i]);
		pthread_detach(philos->id[i]);
	}
	pthread_create(&eat, NULL, eat_control, philos);
	pthread_detach(eat);
}
