/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: splattje <splattje@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 10:26:27 by splattje          #+#    #+#             */
/*   Updated: 2024/09/30 08:57:53 by splattje         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"
#include "cube.h"
#include <sys/time.h>

size_t	get_time(void)
{
	struct timeval	timeval;
	size_t			time;

	if (gettimeofday(&timeval, NULL) == -1)
		return (0);
	time = timeval.tv_sec * 1000 + timeval.tv_usec / 1000;
	return (time);
}
