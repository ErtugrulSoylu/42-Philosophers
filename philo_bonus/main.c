/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdogan <gdogan@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:55:06 by gdogan            #+#    #+#             */
/*   Updated: 2022/04/19 23:44:47 by gdogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	main(int argc, char **argv)
{
	t_philo	philos;

	if (argc != 6 && argc != 5)
		return (printf("Error: Invalid number of arguments\n"));
	if (invalid_arg(argc, argv))
		return (printf("Error: Invalid arguments\n"));
	philos.count = ft_atoi(argv[1]);
	sem_unlink("/life");
	sem_unlink("/kill");
	sem_unlink("/mutex");
	sem_unlink("/msg");
	sem_unlink("/rook");
	philo_init(&philos, argv, argc);
	run_processes(&philos);
	sem_wait(philos.kill);
	kill_processes(&philos);
	return (0);
}
