/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernacar <fernacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 00:13:06 by fernacar          #+#    #+#             */
/*   Updated: 2023/09/20 20:06:04 by fernacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_loop(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->sim_state_lock);
	while (philo->sim->sim_state == ONGOING)
	{
		pthread_mutex_unlock(&philo->sim->sim_state_lock);
		if (philo->fork_left == philo->fork_right)
		{
			philo_log(philo, FORK);
			usleep(philo->sim->settings.time_die * 1000);
			philo_log(philo, DIED);
			pthread_mutex_lock(&philo->sim->sim_state_lock);
			philo->sim->sim_state = CLOSING;
			break ;
		}
		philo_eat_sequence(philo);
		pthread_mutex_lock(&philo->sim->sim_state_lock);
		if (philo->sim->sim_state == CLOSING)
			break ;
		pthread_mutex_unlock(&philo->sim->sim_state_lock);
		philo_log(philo, SLEEP);
		philo_wait(philo, philo->sim->settings.time_sleep * 1000);
		philo_log(philo, THINK);
		philo_wait(philo, 1000);
		pthread_mutex_lock(&philo->sim->sim_state_lock);
	}
	pthread_mutex_unlock(&philo->sim->sim_state_lock);
}

static void	philo_life(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->sim_state_lock);
	pthread_mutex_unlock(&philo->sim->sim_state_lock);
	philo_update_time_ate(philo);
	if (philo->p_id % 2 == 0)
		philo_wait(philo, philo->sim->settings.time_eat * 1000 / 2);
	philo_loop(philo);
}

void	*philo_thread(void *arg)
{
	philo_life((t_philo *) arg);
	return (NULL);
}
