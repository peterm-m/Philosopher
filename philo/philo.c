/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 21:16:43 by pedromar          #+#    #+#             */
/*   Updated: 2024/03/05 22:48:54 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static void	philo_think(t_local *philo, t_share *sh)
{
	printer(philo, MSG_THINK, THINK);
	while (sh->states[philo->fork_one] != 0 && philo->share->dies == 0)
		philo_wait(philo, 10);
	pthread_mutex_lock(&sh->forks[philo->fork_one]);
	memset(&sh->states[philo->fork_one], 1, sizeof(char));
	printer(philo, MSG_TAKE_FORK, FORK);
	while (sh->states[philo->fork_two] != 0 && philo->share->dies == 0)
		philo_wait(philo, 10);
	pthread_mutex_lock(&sh->forks[philo->fork_two]);
	memset(&sh->states[philo->fork_two], 1, sizeof(char));
	printer(philo, MSG_TAKE_FORK, FORK);
}

static void	philo_sleep(t_local *philo, t_share *sh, t_global *gl)
{
	pthread_mutex_unlock(&sh->forks[philo->fork_one]);
	memset(&sh->states[philo->fork_one], 0, sizeof(char));
	pthread_mutex_unlock(&sh->forks[philo->fork_two]);
	memset(&sh->states[philo->fork_two], 0, sizeof(char));
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
}

void	*philosopher(void *arg)
{
	t_local	*philo;

	philo = (t_local *) arg;
	philo->fork_one = MIN((philo->id -1) % philo->global->n_philo,
			philo->id % philo->global->n_philo);
	philo->fork_two = MAX((philo->id -1) % philo->global->n_philo,
			philo->id % philo->global->n_philo);
	philo->time_to_die = philo->global->times[DIE];
	if (philo->global->n_philo == 1)
	{
		printer(philo, MSG_THINK, THINK);
		philo_wait(philo, philo->global->times[DIE]);
	}
	while (philo->share->start == 0)
		;
	while (philo->share->dies == 0
		&& philo->share->complete < philo->global->n_philo)
	{
		philo_think(philo, philo->share);
		philo_eat(philo, philo->share, philo->global);
		philo_sleep(philo, philo->share, philo->global);
	}
	return (NULL);
}
