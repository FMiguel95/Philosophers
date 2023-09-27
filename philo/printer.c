/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernacar <fernacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 17:03:51 by fernacar          #+#    #+#             */
/*   Updated: 2023/09/12 21:32:37 by fernacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	setup_printer(t_sim *sim)
{
	sim->printer.first = NULL;
	sim->printer.last = NULL;
	pthread_mutex_init(&sim->printer.buffer_lock, NULL);
}

void	clean_printer(t_printer *printer)
{
	t_node	*node;
	t_node	*temp;

	pthread_mutex_lock(&printer->buffer_lock);
	node = printer->first;
	while (node != NULL)
	{
		temp = node->next;
		free(node);
		node = temp;
	}
	pthread_mutex_unlock(&printer->buffer_lock);
}

static char	*parse_message(int message_type)
{
	char	*message;

	if (message_type == THINK)
		message = "is thinking";
	else if (message_type == FORK)
		message = "has taken a fork";
	else if (message_type == EAT)
		message = "is eating";
	else if (message_type == SLEEP)
		message = "is sleeping";
	else if (message_type == DIED)
		message = "died";
	else
		message = "all philosophers have finished their meals";
	return (message);
}

static int	print_next_message(t_printer *printer)
{
	long	timestamp;
	int		p_id;
	int		message_type;
	char	*message;
	t_node	*temp;

	pthread_mutex_lock(&printer->buffer_lock);
	if (printer->first == NULL)
	{
		pthread_mutex_unlock(&printer->buffer_lock);
		return (0);
	}
	timestamp = printer->first->timestamp;
	p_id = printer->first->p_id;
	message_type = printer->first->message_type;
	temp = printer->first->next;
	if (printer->first == printer->last)
		printer->last = NULL;
	free(printer->first);
	printer->first = temp;
	pthread_mutex_unlock(&printer->buffer_lock);
	message = parse_message(message_type);
	if (message_type != DONE)
		printf("%d %d %s\n", (int)timestamp, p_id, message);
	return (message_type == DIED || message_type == DONE);
}

void	*printer_thread(void *arg)
{
	t_printer	*printer;

	printer = (t_printer *)arg;
	while (1)
	{
		if (print_next_message(printer))
			break ;
	}
	return (NULL);
}
