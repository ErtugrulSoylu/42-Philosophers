/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdogan <gdogan@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:54:36 by gdogan            #+#    #+#             */
/*   Updated: 2022/04/19 15:56:21 by gdogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_processes(t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < philos->count)
		kill(philos->id[i], SIGQUIT);
}

void	*eat_control(void *arg)
{
	t_philo	*philos;
	int		i;

	i = -1;
	philos = (t_philo *)arg;
	while (++i < philos->count)
		sem_wait(philos->life);
	kill_processes(philos);
	printf("everybody ate\n");
	exit(0);
}

void	philo_init(t_philo *philos, char **argv, int argc)
{
	philos->id = (pid_t *)malloc(philos->count * sizeof(pid_t));
	philos->eaten = 0;
	philos->last_eat = 0;
	philos->die_time = ft_atoi(argv[2]);
	philos->eat_time = ft_atoi(argv[3]);
	philos->sleep_time = ft_atoi(argv[4]);
	philos->eat_count = 2147483647;
	if (argc == 6)
		philos->eat_count = ft_atoi(argv[5]);
	if (philos->eat_count == 0)
		exit(printf("everybody ate!\n"));
	philos->life = sem_open("/life", O_CREAT | O_EXCL, 0644, philos->count);
	philos->kill = sem_open("/kill", O_CREAT | O_EXCL, 0644, philos->count);
	philos->mutex = sem_open("/mutex", O_CREAT | O_EXCL, 0644, philos->count);
	philos->msg = sem_open("/msg", O_CREAT | O_EXCL, 0644, 1);
	philos->rook = sem_open("/rook", O_CREAT | O_EXCL, 0644, philos->count);
	sem_wait(philos->rook);
}

void	run_processes(t_philo *philos)
{
	int			i;
	pthread_t	eat;

	i = -1;
	gettimeofday(&philos->start, NULL);
	while (++i < philos->count)
	{
		philos->id[i] = fork();
		if (philos->id[i] == 0)
			philo(philos, i);
	}
	usleep(50000);
	pthread_create(&eat, NULL, eat_control, philos);
	pthread_detach(eat);
}
