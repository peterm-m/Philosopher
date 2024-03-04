/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 21:16:43 by pedromar          #+#    #+#             */
/*   Updated: 2024/03/04 18:39:15 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	philo_wait(t_local *philo, t_time wait)
{
	wait = MIN(wait, philo->time_to_die);
	usleep(wait);
	philo->time = timer();
	if (wait == philo->time_to_die)
		printer(philo, MSG_DIE, DIE);
	else
		philo->time_to_die -= wait;
}

static void	philo_think(t_local *philo, t_share *sh, t_global *gl)
{
	printer(philo, MSG_THINK, THINK);
	sem_wait(SEM_FORKS);
	printer(philo, MSG_TAKE_FORK, FORK);
	printer(philo, MSG_TAKE_FORK, FORK);
}

static void	philo_sleep(t_local *philo, t_share *sh, t_global *gl)
{
	printer(philo, MSG_SLEEP, SLEEP);
	philo_wait(philo, gl->times[SLEEP]);
}

static void	philo_eat(t_local *philo, t_share *sh, t_global *gl)
{
	static int	n_eats[PTHREAD_THREAD_MAX];

	philo->time_to_die = gl->times[DIE];
	printer(philo, MSG_EAT, EAT);
	philo_wait(philo, gl->times[EAT]);
	if (n_eats[philo->id -1]++ == gl->n_eats)
		memset(&(sh->complete), sh->complete +1,
			sizeof(int));
	sem_post(SEM_FORKS);
}

void	*philosopher(t_global *global, t_share *share, int id)
{
	t_local	philo;

	philo.id = id;
	philo.time = 0;
	philo.time_to_die = global->times[DIE];
	philo.global = global;
	philo.share = share;
	if (global->n_philo == 1)
	{
		printer(&philo, MSG_THINK, THINK);
		philo_wait(&philo, global->times[DIE]);
	}
	while (share->dies == 0
		&& share->complete < global->n_philo)
	{
		philo_think(&philo, share, global);
		philo_eat(&philo, share, global);
		philo_sleep(&philo, share, global);
	}
}
