/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromar <pedromar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:08:18 by pedromar          #+#    #+#             */
/*   Updated: 2024/03/05 17:33:34 by pedromar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <sys/types.h>
# include <sys/time.h>
# include <sys/param.h>

# include <fcntl.h>
# include <semaphore.h>
# include <sys/wait.h>
# include <errno.h>
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

# define NO_EATING 0
# define EATING 1

# define PTHREAD_THREAD_MAX 256

# define SEM_PRINT "/print"
# define SEM_FORKS "/forks"
# define SEM_CHAIRS "/chairs"
# define SEM_FINISH "/finishes"

typedef long long int	t_time;

struct					s_local;
struct					s_global;

typedef struct s_local
{
	int				id;
	t_time			time;
	t_time			time_to_die;
	int				eating;
	sem_t			*screen;
	sem_t			*forks;
	sem_t			*chairs;
	sem_t			*finishes;
}	t_local;

typedef struct s_global
{
	int		n_philo;
	int		n_eats;
	t_time	times[3];
}	t_global;

t_time	timer(void);
void	printer(t_local *philo, const char *log, int action);
void	philosopher(t_global *global, t_local *philo);

#endif
