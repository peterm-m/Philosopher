/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromar <pedromar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 17:43:58 by pedromar          #+#    #+#             */
/*   Updated: 2024/03/05 17:45:59 by pedromar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

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
