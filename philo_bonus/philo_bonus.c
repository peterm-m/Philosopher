/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromar <pedromar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 21:16:43 by pedromar          #+#    #+#             */
/*   Updated: 2024/03/05 17:52:42 by pedromar         ###   ########.fr       */
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

static void	*philo_think(void *arg)
{
	t_local	*philo;

	printer(philo, MSG_THINK, THINK);
	philo = (t_local *)arg;
	while (philo->eating == NO_EATING)
		philo_wait(philo, 10);
	return (NULL);
}

static void	philo_eat(t_local *philo, t_global *gl)
{
	sem_wait(philo->chairs);
	sem_wait(philo->forks);
	printer(philo, MSG_TAKE_FORK, FORK);
	sem_wait(philo->forks);
	memset(&philo->eating, EATING, sizeof(int));
	printer(philo, MSG_TAKE_FORK, FORK);
	philo->time_to_die = gl->times[DIE];
	printer(philo, MSG_EAT, EAT);
	philo_wait(philo, gl->times[EAT]);
	if (gl->n_eats-- == 0)
		sem_post(philo->finishes);
	memset(&philo->eating, NO_EATING, sizeof(int));
	sem_post(philo->forks);
	sem_post(philo->forks);
	sem_post(philo->chairs);
}

void	philosopher(t_global *global, t_local *philo)
{
	pthread_t	think_thread;

	if (global->n_philo == 1)
	{
		printer(philo, MSG_THINK, THINK);
		philo_wait(philo, global->times[DIE]);
	}
	while (1)
	{
		if (pthread_create(&think_thread, NULL, philo_think, philo))
			exit(EXIT_FAILURE);
		pthread_detach(think_thread);
		philo_eat(philo, global);
		printer(philo, MSG_SLEEP, SLEEP);
		philo_wait(philo, global->times[SLEEP]);
	}
}
