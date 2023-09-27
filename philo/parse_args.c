/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernacar <fernacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 01:07:58 by fernacar          #+#    #+#             */
/*   Updated: 2023/09/10 23:54:20 by fernacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi(char *str)
{
	long	value;
	int		sign;

	value = 0;
	sign = 1;
	while (*str == ' ' || *str == '\t')
		str++;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		value = value * 10 + (*str - '0');
		if (value > INT_MAX)
			return (0);
		str++;
	}
	return (sign * value);
}

int	parse_args(int ac, char **av, t_settings *settings)
{
	settings->n_philos = ft_atoi(av[1]);
	settings->time_die = ft_atoi(av[2]);
	settings->time_eat = ft_atoi(av[3]);
	settings->time_sleep = ft_atoi(av[4]);
	settings->eat_ammount = 0;
	if (ac == 6)
		settings->eat_ammount = ft_atoi(av[5]);
	if (settings->n_philos <= 0)
		printf("Invalid number_of_philosophers!\n");
	if (settings->time_die <= 0)
		printf("Invalid time_to_die!\n");
	if (settings->time_eat <= 0)
		printf("Invalid time_to_eat!\n");
	if (settings->time_sleep <= 0)
		printf("Invalid time_to_sleep!\n");
	if (ac == 6 && settings->eat_ammount <= 0)
		printf("Invalid number_of_times_each_philosopher_must_eat!\n");
	if (settings->n_philos <= 0 || settings->time_die <= 0
		|| settings->time_eat <= 0 || settings->time_sleep <= 0
		|| (ac == 6 && settings->eat_ammount <= 0))
		return (0);
	return (1);
}
