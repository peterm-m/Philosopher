/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromar <pedromar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:50:42 by pedromar          #+#    #+#             */
/*   Updated: 2024/03/04 20:34:10 by pedromar         ###   ########.fr       */
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

void	printer(t_local *philo, const char *log, int action)
{
	sem_wait(philo->share->screen);
	philo->time = timer();
	printf("%lld %d %s\n", philo->time / 1000, philo->id, log);
	if (action == DIE)
		exit(EXIT_FAILURE);
	sem_post(philo->share->screen);
	return ;
}

static int	parser(char const **argv, t_global *global, t_share *share)
{
	global->n_philo = (int) get_uint(argv[1]);
	global->times[DIE] = get_uint(argv[2]) * 1000;
	global->times[EAT] = get_uint(argv[3]) * 1000;
	global->times[SLEEP] = get_uint(argv[4]) * 1000;
	global->n_eats = -1;
	if (argv[5] != 0)
		global->n_eats = (int) get_uint(argv[5]);
	if (global->n_philo < 1 || global->n_philo > PTHREAD_THREAD_MAX
		|| global->times[DIE] <= 0
		|| global->times[EAT] <= 0
		|| global->times[SLEEP] <= 0
		|| (argv[5] && global->n_eats < 0))
		return (EXIT_FAILURE);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_FINISH);
	share->screen = sem_open(SEM_PRINT, O_CREAT | O_EXCL, 0640, 1);
	share->finishe = sem_open(SEM_FINISH, O_CREAT | O_EXCL, 0640, 1);
	share->forks = sem_open(SEM_FORKS, O_CREAT | O_EXCL, 0640,
			global->n_philo -1);
	if (share->screen == SEM_FAILED || share->forks == SEM_FAILED
			|| share->finishe == SEM_FAILED)
		exit (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	launcher(t_global *global, t_share *share)
{
	pid_t	pid[PTHREAD_THREAD_MAX];
	t_local	local;

	local.id = -1;
	local.global = global;
	local.share = share;
	local.time_to_die = global->times[DIE];
	local.time = 0;
	while (++local.id < global->n_philo)
	{
		pid[local.id] = fork();
		if (pid[local.id] == 0)
			philosopher(global, share, &local);
		else if (pid[local.id] < 0)
			kill(-1, SIGTERM);
	}
}

int	main(int argc, char const **argv)
{
	t_global	global;
	t_share		share;

	if (argc > 6 || argc < 5)
	{
		printf("%s\n", "Incorrect number of parameters");
		exit (EXIT_FAILURE);
	}
	else if (parser(argv, &global, &share))
	{
		printf("%s\n", "Parser Error");
		exit (EXIT_FAILURE);
	}
	else if (launcher(&global, &share))
	{
		printf("%s\n", "Launcher Error");
		exit (EXIT_FAILURE);
	}
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_FINISH);
	return (EXIT_FAILURE);
}
