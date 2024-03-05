/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pedromar <pedromar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 16:08:18 by pedromar          #+#    #+#             */
/*   Updated: 2024/03/05 18:00:38 by pedromar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOOLS_H
# define TOOLS_H

# include <sys/types.h>
# include <sys/param.h>

# include <limits.h>
# include <sys/time.h>
# include <stdlib.h>

# define PTHREAD_THREAD_MAX 256

typedef long long int	t_time;

t_time			timer(void);
long long int	get_uint(const char *str);


#endif