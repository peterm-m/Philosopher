/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:08:18 by pedromar          #+#    #+#             */
/*   Updated: 2023/11/06 21:55:30 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <sys/types.h>
# include <sys/time.h>
# include <sys/param.h>

# include <fcntl.h>
# include <semaphore.h>
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

# define SEM_MUTEX_PRINT "/print"
# define SEM_FORKS "/forks"

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
	int		n_philo;
	int		n_eats;
	t_time	times[3];
}	t_global;

typedef struct s_share
{
	char	start;
	char	complete;
	char	dies;
	sem_t	*screen;
	sem_t	*forks;
}	t_share;

t_time	timer(void);
void	printer(t_local *philo, const char *log, int action);
void	*philosopher(t_global *global, t_share *share, int id);

#endif