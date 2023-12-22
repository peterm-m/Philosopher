/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromar <pedromar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:08:18 by pedromar          #+#    #+#             */
/*   Updated: 2023/11/06 16:57:33 by pedromar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/types.h>
# include <sys/time.h>
# include <sys/param.h>

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>

# include "tools.h"

# define MSG_EAT "is eating"
# define MSG_THINK "is thinking"
# define MSG_SLEEP "is sleeping"
# define MSG_TAKE_FORK "has taken fork"
# define MSG_DIE "died"

enum
{
	DIE,
	SLEEP,
	EAT,
	THINK,
	FORK
};

# define PTHREAD_THREAD_MAX 256

typedef long long int	t_time;

struct					s_local;
struct					s_global;
struct					s_share;

typedef struct s_local
{
	int				id;
	int				fork_one;
	int				fork_two;
	t_time			time;
	t_time			time_to_die;
	struct s_global	*global;
	struct s_share	*share;
}	t_local;

typedef struct s_global
{
	int				n_philo;
	int				n_eats;
	t_time			times[3];
}	t_global;

typedef struct s_share
{
	char			start;
	char			complete;
	char			dies;
	char			states[PTHREAD_THREAD_MAX];
	pthread_mutex_t	forks[PTHREAD_THREAD_MAX];
}	t_share;

t_time	timer(void);
void	printer(t_local *philo, const char *log, int action);
void	*philosopher(void *philo);

#endif