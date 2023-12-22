/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_number.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromar <pedromar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 17:24:33 by pedro             #+#    #+#             */
/*   Updated: 2023/11/06 16:55:26 by pedromar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tools.h"

static long long int	ft_atol(const char *str)
{
	unsigned long long int	c;
	int						sing;

	c = 0LL;
	sing = 1;
	while (*str == ' ' || (*str < 14 && *str > 8))
		str++;
	if (*str == '-' || *str == '+')
	{
		sing = 44 - *str;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		c = (c * 10) + (*str - '0');
		str++;
	}
	if (c > LONG_MAX && sing == 1)
		return (-1);
	if (c > (unsigned long long int)(-LLONG_MIN) && sing == -1)
		return (0);
	return (c * sing);
}

static int	isnum(const char *str)
{
	while (*str == ' ' || (*str < 14 && *str > 8))
		str++;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
		str++;
	if (*str != '\0')
		return (0);
	else
		return (1);
}

long long int	get_uint(const char *str)
{
	long long int	res;

	if (isnum(str) == 0)
		return (0);
	res = ft_atol(str);
	if (res > INT_MAX || res < 0)
		return (-1);
	return (res);
}
