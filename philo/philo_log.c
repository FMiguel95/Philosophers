/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_log.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernacar <fernacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 20:54:38 by fernacar          #+#    #+#             */
/*   Updated: 2023/09/12 20:55:15 by fernacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_log(t_philo *philo, int message_type)
{
	t_node	*new_node;

	new_node = malloc(sizeof(t_node));
	new_node->p_id = philo->p_id;
	new_node->message_type = message_type;
	new_node->next = NULL;
	pthread_mutex_lock(&philo->sim->printer.buffer_lock);
	new_node->timestamp = get_current_time() - philo->sim->start_time;
	if (philo->sim->printer.last != NULL)
	{
		philo->sim->printer.last->next = new_node;
		philo->sim->printer.last = new_node;
	}
	else
	{
		philo->sim->printer.first = new_node;
		philo->sim->printer.last = new_node;
	}
	pthread_mutex_unlock(&philo->sim->printer.buffer_lock);
}

void	philo_log_end(t_philo *philo, int message_type)
{
	pthread_mutex_lock(&philo->sim->sim_state_lock);
	if (philo->sim->sim_state == ONGOING)
	{
		philo_log(philo, message_type);
		philo->sim->sim_state = CLOSING;
		pthread_mutex_unlock(&philo->sim->sim_state_lock);
	}
	else
		pthread_mutex_unlock(&philo->sim->sim_state_lock);
}
