/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromar <pedromar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:50:42 by pedromar          #+#    #+#             */
/*   Updated: 2024/03/05 17:34:37 by pedromar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_time	timer(void)
{
	static struct timeval	time0 = {.tv_sec = 0, .tv_usec = 0};
	struct timeval			time;

	if (time0.tv_sec == 0 && time0.tv_usec == 0)
		gettimeofday(&time0, NULL);
	gettimeofday(&time, NULL);
	return ((time.tv_sec - time0.tv_sec) * 1000000
		+ (time.tv_usec - time0.tv_usec));
}

static int	parser(char const **argv, t_global *gl, t_local *ph)
{
	gl->n_philo = (int) get_uint(argv[1]);
	gl->times[DIE] = get_uint(argv[2]) * 1000;
	gl->times[EAT] = get_uint(argv[3]) * 1000;
	gl->times[SLEEP] = get_uint(argv[4]) * 1000;
	gl->n_eats = -1;
	if (argv[5] != 0)
		gl->n_eats = (int) get_uint(argv[5]);
	if (gl->n_philo < 1 || gl->n_philo > PTHREAD_THREAD_MAX
		|| gl->times[DIE] <= 0
		|| gl->times[EAT] <= 0
		|| gl->times[SLEEP] <= 0
		|| (argv[5] && gl->n_eats < 0))
		return (EXIT_FAILURE);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_CHAIRS);
	sem_unlink(SEM_FINISH);
	ph->screen = sem_open(SEM_PRINT, O_CREAT | O_EXCL, 0640, 1);
	ph->chairs = sem_open(SEM_CHAIRS, O_CREAT | O_EXCL, 0640, gl->n_philo -1);
	ph->forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL, 0640, gl->n_philo);
	ph->finishes = sem_open(SEM_FINISH, O_CREAT | O_EXCL, 0640, gl->n_philo);
	if (ph->screen == SEM_FAILED || ph->forks == SEM_FAILED
		|| ph->chairs == SEM_FAILED || ph->finishes == SEM_FAILED)
		exit (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	*wait_end(void *arg)
{
	t_local	*philo;

	philo = arg;
	while (philo->id-- > 0)
	{
		sem_wait(philo->finishes);
		sem_post(philo->finishes);
	}
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_CHAIRS);
	sem_unlink(SEM_FINISH);
	kill(-1, SIGTERM);
	return (NULL);
}

static int	launcher(t_global *global, t_local *philo)
{
	pid_t		pid;
	pthread_t	thread_finish;

	philo->id = -1;
	philo->eating = 0;
	philo->time_to_die = global->times[DIE];
	while (++philo->id < global->n_philo)
	{
		pid = fork();
		if (pid == 0)
		{
			philo->time = timer();
			sem_wait(philo->finishes);
			philosopher(global, philo);
		}
		else if (pid < 0)
			return (EXIT_FAILURE);
	}
	if (pthread_create(&thread_finish, NULL, wait_end, philo))
		exit(EXIT_FAILURE);
	pthread_detach(thread_finish);
	waitpid(-1, NULL, 0);
	return (EXIT_SUCCESS);
}

int	main(int argc, char const **argv)
{
	t_global	global;
	t_local		philo;

	if (argc > 6 || argc < 5)
	{
		printf("%s\n", "Incorrect number of parameters");
		exit (EXIT_FAILURE);
	}
	else if (parser(argv, &global, &philo))
	{
		printf("%s\n", "Parser Error");
		exit (EXIT_FAILURE);
	}
	if (launcher(&global, &philo))
		printf("%s\n", "Launcher Error");
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_CHAIRS);
	sem_unlink(SEM_FINISH);
	kill(-1, SIGTERM);
	exit (EXIT_SUCCESS);
}
