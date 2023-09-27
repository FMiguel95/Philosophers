/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fernacar <fernacar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 00:12:38 by fernacar          #+#    #+#             */
/*   Updated: 2023/09/20 20:21:51 by fernacar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>

# include <unistd.h>

struct	s_sim;
struct	s_philo;

# define THINK	0
# define FORK	1
# define EAT	2
# define SLEEP	3
# define DIED	4
# define DONE	5

typedef struct s_node{
	long			timestamp;
	int				p_id;
	int				message_type;
	struct s_node	*next;
}			t_node;

typedef struct s_printer{
	pthread_t		tid;
	t_node			*first;
	t_node			*last;
	pthread_mutex_t	buffer_lock;
}			t_printer;

typedef struct s_settings{
	int	n_philos;
	int	time_die;
	int	time_eat;
	int	time_sleep;
	int	eat_ammount;
}				t_settings;

typedef struct s_fork{
	pthread_mutex_t	lock;
	struct s_philo	*holder;
}				t_fork;

typedef struct s_philo{
	pthread_t		tid;
	int				p_id;
	t_fork			*fork_right;
	t_fork			*fork_left;
	long			time_ate;
	pthread_mutex_t	time_ate_lock;
	int				times_eaten;
	pthread_mutex_t	times_eaten_lock;
	struct s_sim	*sim;
}				t_philo;

# define ONGOING	0
# define CLOSING	1

typedef struct s_sim{
	int				sim_state;
	t_settings		settings;
	pthread_t		watcher_tid;
	t_printer		printer;
	long			start_time;
	t_philo			*philo_list;
	t_fork			*fork_list;
	int				philos_done;
	pthread_mutex_t	sim_state_lock;
	pthread_mutex_t	philos_done_lock;
}				t_sim;

int		parse_args(int ac, char **av, t_settings *settings);

long	get_current_time(void);

void	setup(t_sim *sim);
void	cleanup(t_sim *sim);
void	setup_printer(t_sim *sim);
void	*printer_thread(void *arg);
void	clean_printer(t_printer *printer);

void	*watcher_thread(void *arg);

void	philo_log(t_philo *philo, int message_type);
void	philo_log_end(t_philo *philo, int message_type);
void	check_eaten(t_sim *sim);
void	philo_wait(t_philo *philo, int time);

void	philo_eat_sequence(t_philo *philo);
void	philo_update_time_ate(t_philo *philo);

void	*philo_thread(void *arg);

#endif
