/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdogan <gdogan@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:51:04 by gdogan            #+#    #+#             */
/*   Updated: 2022/04/19 15:51:08 by gdogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	smart_sleep(t_philo *p, long long ms)
{
	long long	begin;

	begin = gettime(&p->start);
	while (gettime(&p->start) - begin < ms)
		usleep(100);
}

int	main(int argc, char **argv)
{
	t_philo	philos;

	if (argc != 6 && argc != 5)
		return (printf("Error: Invalid number of arguments\n"));
	if (invalid_arg(argc, argv))
		return (printf("Error: Invalid arguments\n"));
	philos.count = ft_atoi(argv[1]);
	philo_init(&philos, argv, argc);
	run_threads(&philos);
	death_control(&philos);
	return (0);
}
