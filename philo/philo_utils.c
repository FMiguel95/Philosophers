/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernacar <fernacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 00:21:51 by fernacar          #+#    #+#             */
/*   Updated: 2023/09/20 20:18:55 by fernacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	philo_check_dead(t_philo *philo)
// {
// 	if (get_current_time() - philo->time_ate > philo->sim->settings.time_die)
// 	{
// 		philo_log_end(philo, DIED);
// 		return (1);
// 	}
// 	return (0);
// }

static int	all_done_eating(t_sim *sim)
{
	int	is_done;
	int	i;

	i = 0;
	while (i < sim->settings.n_philos)
	{
		pthread_mutex_lock(&sim->philo_list[i].times_eaten_lock);
		is_done = sim->philo_list[i].times_eaten >= sim->settings.eat_ammount;
		pthread_mutex_unlock(&sim->philo_list[i].times_eaten_lock);
		if (!is_done)
			break ;
		i++;
	}
	return (is_done);
}

void	check_eaten(t_sim *sim)
{
	pthread_mutex_lock(&sim->sim_state_lock);
	while (sim->sim_state == ONGOING)
	{
		pthread_mutex_unlock(&sim->sim_state_lock);
		if (all_done_eating(sim))
		{
			philo_log_end(&sim->philo_list[0], DONE);
			pthread_mutex_lock(&sim->sim_state_lock);
			break ;
		}
		pthread_mutex_lock(&sim->sim_state_lock);
	}
	pthread_mutex_unlock(&sim->sim_state_lock);
}

void	philo_wait(t_philo *philo, int time)
{
	long	wait_start;

	wait_start = get_current_time();
	time /= 1000;
	while ((get_current_time() - wait_start) < time)
	{
		pthread_mutex_lock(&philo->sim->sim_state_lock);
		if (philo->sim->sim_state == ONGOING)
		{
			pthread_mutex_unlock(&philo->sim->sim_state_lock);
			usleep(500);
		}
		else
		{
			pthread_mutex_unlock(&philo->sim->sim_state_lock);
			break ;
		}
	}
}
