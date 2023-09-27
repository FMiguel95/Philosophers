/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernacar <fernacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 23:51:15 by fernacar          #+#    #+#             */
/*   Updated: 2023/09/20 17:12:23 by fernacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_threads(t_sim *sim)
{
	int	i;

	pthread_create(&sim->printer.tid, NULL, printer_thread,
		(void *)&sim->printer);
	pthread_create(&sim->watcher_tid, NULL, watcher_thread,
		(void *)sim);
	i = 0;
	while (i < sim->settings.n_philos)
	{
		pthread_create(&sim->philo_list[i].tid, NULL, philo_thread,
			(void *)&sim->philo_list[i]);
		i++;
	}
}

void	wait_threads(t_sim *sim)
{
	int	i;

	if (sim->settings.eat_ammount)
		check_eaten(sim);
	pthread_join(sim->printer.tid, NULL);
	pthread_join(sim->watcher_tid, NULL);
	i = 0;
	while (i < sim->settings.n_philos)
	{
		pthread_join(sim->philo_list[i].tid, NULL);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_sim			sim;

	sim = (t_sim){0};
	if (ac != 5 && ac != 6)
		printf("Usage: ./philo <number_of_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep> \
[number_of_times_each_philosopher_must_eat]\n");
	else if (parse_args(ac, av, &sim.settings))
	{
		setup(&sim);
		pthread_mutex_lock(&sim.sim_state_lock);
		start_threads(&sim);
		sim.start_time = get_current_time();
		pthread_mutex_unlock(&sim.sim_state_lock);
		wait_threads(&sim);
		cleanup(&sim);
	}
	return (0);
}
