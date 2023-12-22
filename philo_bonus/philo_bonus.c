/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 21:16:43 by pedromar          #+#    #+#             */
/*   Updated: 2023/11/07 09:33:05 by pedro            ###   ########.fr       */
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
	//while (sh->states[philo->fork_one] != 0 && philo->share->dies == 0)
	//	philo_wait(philo, 10);
	sem_wait(sh->forks);
	//memset(&sh->states[philo->fork_one], 1, sizeof(char));
	printer(philo, MSG_TAKE_FORK, FORK);
	//while (sh->states[philo->fork_two] != 0 && philo->share->dies == 0)
	//	philo_wait(philo, 10);
	sem_wait(sh->forks);
	//memset(&sh->states[philo->fork_two], 1, sizeof(char));
	printer(philo, MSG_TAKE_FORK, FORK);
}

static void	philo_sleep(t_local *philo, t_share *sh, t_global *gl)
{
	sem_post(sh->forks);
	//memset(&sh->states[philo->fork_one], 0, sizeof(char));
	sem_post(sh->forks);
	//memset(&sh->states[philo->fork_two], 0, sizeof(char));
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

void	*philosopher(t_global *global, t_share *share, int id)
{
	share->screen = sem_open(SEM_MUTEX_PRINT);
	printf("hola id %d\n", id);
//	t_local	*philo;
//
//	philo = (t_local *) arg;
//	philo->fork_one = MIN((philo->id -1) % philo->global->n_philo,
//			philo->id % philo->global->n_philo);
//	philo->fork_two = MAX((philo->id -1) % philo->global->n_philo,
//			philo->id % philo->global->n_philo);
//	philo->time_to_die = philo->global->times[DIE];
//	if (philo->global->n_philo == 1)
//	{
//		printer(philo, MSG_THINK, THINK);
//		philo_wait(philo, philo->global->times[DIE]);
//	}
//	while (philo->share->start == 0)
//		;
//	while (philo->share->dies == 0
//		&& philo->share->complete < philo->global->n_philo)
//	{
//		philo_think(philo, philo->share, philo->global);
//		philo_eat(philo, philo->share, philo->global);
//		philo_sleep(philo, philo->share, philo->global);
//	}
	exit(0);
}
