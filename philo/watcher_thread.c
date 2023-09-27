/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   watcher_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernacar <fernacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:03:56 by fernacar          #+#    #+#             */
/*   Updated: 2023/09/20 20:21:39 by fernacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	check_philo_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->time_ate_lock);
	if (get_current_time() - philo->time_ate >= philo->sim->settings.time_die)
	{
		philo_log_end(philo, DIED);
		pthread_mutex_unlock(&philo->time_ate_lock);
		return ;
	}
	pthread_mutex_unlock(&philo->time_ate_lock);
}

static void	watcher_loop(t_sim *sim)
{
	int	i;

	while (1)
	{
		pthread_mutex_lock(&sim->sim_state_lock);
		if (sim->sim_state != ONGOING)
			break ;
		pthread_mutex_unlock(&sim->sim_state_lock);
		i = 0;
		while (i < sim->settings.n_philos)
		{
			check_philo_death(&sim->philo_list[i]);
			i++;
		}
	}
	pthread_mutex_unlock(&sim->sim_state_lock);
}

void	*watcher_thread(void *arg)
{
	t_sim	*sim;

	sim = (t_sim *)arg;
	pthread_mutex_lock(&sim->sim_state_lock);
	pthread_mutex_unlock(&sim->sim_state_lock);
	watcher_loop((t_sim *)arg);
	return (NULL);
}
