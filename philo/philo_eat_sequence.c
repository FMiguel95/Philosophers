/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eat_sequence.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernacar <fernacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 23:44:50 by fernacar          #+#    #+#             */
/*   Updated: 2023/09/20 20:22:12 by fernacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	philo_drop_forks(t_philo *philo)
{
	t_fork	*fork1;
	t_fork	*fork2;

	fork1 = philo->fork_left;
	fork2 = philo->fork_right;
	if (philo->p_id % 2 == 0)
	{
		fork1 = philo->fork_right;
		fork2 = philo->fork_left;
	}
	fork1->holder = NULL;
	pthread_mutex_unlock(&fork1->lock);
	fork2->holder = NULL;
	pthread_mutex_unlock(&fork2->lock);
}

static void	philo_eat(t_philo *philo)
{
	philo_log(philo, EAT);
	philo_update_time_ate(philo);
	philo_wait(philo, philo->sim->settings.time_eat * 1000);
	pthread_mutex_lock(&philo->times_eaten_lock);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->times_eaten_lock);
}

static void	philo_take_forks(t_philo *philo)
{
	t_fork	*fork1;
	t_fork	*fork2;

	fork1 = philo->fork_left;
	fork2 = philo->fork_right;
	if (philo->p_id % 2 == 0)
	{
		fork1 = philo->fork_right;
		fork2 = philo->fork_left;
	}
	pthread_mutex_lock(&fork1->lock);
	fork1->holder = philo;
	philo_log(philo, FORK);
	pthread_mutex_lock(&fork2->lock);
	fork2->holder = philo;
	philo_log(philo, FORK);
}

void	philo_eat_sequence(t_philo *philo)
{
	philo_take_forks(philo);
	philo_eat(philo);
	philo_drop_forks(philo);
}

void	philo_update_time_ate(t_philo *philo)
{
	pthread_mutex_lock(&philo->time_ate_lock);
	philo->time_ate = get_current_time();
	pthread_mutex_unlock(&philo->time_ate_lock);
}
