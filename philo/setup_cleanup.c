/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_cleanup.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernacar <fernacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 21:41:38 by fernacar          #+#    #+#             */
/*   Updated: 2023/09/20 00:32:02 by fernacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	setup_philos(t_sim *sim)
{
	int	i;

	sim->philo_list = malloc(sizeof(t_philo) * sim->settings.n_philos);
	sim->fork_list = malloc(sizeof(t_fork) * sim->settings.n_philos);
	i = 0;
	while (i < sim->settings.n_philos)
	{
		sim->philo_list[i].fork_right = &sim->fork_list[i];
		if (i == 0)
			sim->philo_list[i].fork_left = \
			&sim->fork_list[sim->settings.n_philos - 1];
		else
			sim->philo_list[i].fork_left = &sim->fork_list[i - 1];
		sim->philo_list[i].p_id = i + 1;
		sim->philo_list[i].sim = sim;
		sim->philo_list[i].time_ate = LONG_MAX;
		sim->philo_list[i].times_eaten = 0;
		pthread_mutex_init(&sim->philo_list[i].time_ate_lock, NULL);
		pthread_mutex_init(&sim->philo_list[i].times_eaten_lock, NULL);
		pthread_mutex_init(&sim->fork_list[i].lock, NULL);
		sim->fork_list[i].holder = NULL;
		i++;
	}
}

void	setup(t_sim *sim)
{
	setup_printer(sim);
	pthread_mutex_init(&sim->sim_state_lock, NULL);
	pthread_mutex_init(&sim->philos_done_lock, NULL);
	setup_philos(sim);
	sim->sim_state = ONGOING;
}

void	cleanup(t_sim *sim)
{
	int	i;

	clean_printer(&sim->printer);
	pthread_mutex_destroy(&sim->printer.buffer_lock);
	pthread_mutex_destroy(&sim->sim_state_lock);
	i = 0;
	while (i < sim->settings.n_philos)
	{
		pthread_mutex_destroy(&sim->philo_list[i].time_ate_lock);
		pthread_mutex_destroy(&sim->philo_list[i].times_eaten_lock);
		pthread_mutex_destroy(&sim->fork_list[i].lock);
		i++;
	}
	free(sim->philo_list);
	free(sim->fork_list);
}
