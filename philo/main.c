/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedro <pedro@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:50:42 by pedromar          #+#    #+#             */
/*   Updated: 2024/03/05 23:30:19 by pedro            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printer(t_local *philo, const char *log, int action)
{
	static pthread_mutex_t	screen = PTHREAD_MUTEX_INITIALIZER;

	pthread_mutex_lock(&screen);
	philo->time = timer();
	if (philo->share->dies == 0)
		printf("%lld %d %s\n", philo->time / 1000, philo->id, log);
	if (action == DIE)
	{
		memset(&(philo->share->dies), 1, sizeof(char));
		usleep(10);
	}
	pthread_mutex_unlock(&screen);
	return ;
}

static int	parser(char const **argv, t_global *global, t_share *share)
{
	int	i;

	global->n_philo = (int) get_uint(argv[1]);
	global->times[DIE] = get_uint(argv[2]) * 1000;
	global->times[EAT] = get_uint(argv[3]) * 1000;
	global->times[SLEEP] = get_uint(argv[4]) * 1000;
	global->n_eats = -1;
	if (argv[5] != 0)
		global->n_eats = (int) get_uint(argv[5]);
	i = -1;
	while (++i < global->n_philo)
		if (pthread_mutex_init(&(share->forks[i]), NULL))
			break ;
	while (i < global->n_philo && i >= 0)
		pthread_mutex_destroy(&(share->forks[i--]));
	if (global->n_philo < 1 || global->n_philo > 256
		|| global->times[EAT] <= 0
		|| global->times[DIE] <= 0
		|| global->times[SLEEP] <= 0
		|| (argv[5] && global->n_eats < 0) || i < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static int	launcher(t_global *global, t_share *share)
{
	pthread_t	threads[PTHREAD_THREAD_MAX];
	t_local		philos[PTHREAD_THREAD_MAX];
	int			i;

	i = -1;
	memset(&share->states, 0, sizeof(char) * PTHREAD_THREAD_MAX);
	memset(&share->complete, 0, sizeof(char));
	memset(&share->dies, 0, sizeof(char));
	memset(&share->start, 0, sizeof(char));
	while (++i < global->n_philo)
	{
		philos[i].id = i +1;
		philos[i].share = share;
		philos[i].global = global;
		if (pthread_create(&threads[i], NULL,
				philosopher, &philos[i]))
			return (EXIT_FAILURE);
	}
	memset(&share->start, 1, sizeof(char));
	while (--i >= 0)
		pthread_join(threads[i], NULL);
	while (++i < global->n_philo)
		pthread_mutex_destroy(&(share->forks[i]));
	return (EXIT_SUCCESS);
}

int	main(int argc, char const **argv)
{
	t_global	global;
	t_share		share;

	if (argc > 6 || argc < 5)
	{
		printf("%s\n", "Incorrect number of parameters");
		return (EXIT_FAILURE);
	}
	else if (parser(argv, &global, &share))
	{
		printf("%s\n", "Parser Error");
		return (EXIT_FAILURE);
	}
	else if (launcher(&global, &share))
	{
		printf("%s\n", "Launcher Error");
		return (EXIT_FAILURE);
	}
	else
		return (EXIT_SUCCESS);
}
