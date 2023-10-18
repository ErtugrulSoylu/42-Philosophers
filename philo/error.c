/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdogan <gdogan@student.42istanbul.com.tr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:49:46 by gdogan            #+#    #+#             */
/*   Updated: 2022/04/19 15:49:53 by gdogan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_valid(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (0);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		i++;
	if (str[i] != '\0')
		return (0);
	else if (ft_atoi(str) == 2147483648)
		return (0);
	return (1);
}

int	invalid_arg(int argc, char **argv)
{
	int	i;

	i = 0;
	while (++i < argc)
		if (!is_valid(argv[i]))
			return (1);
	return (0);
}
