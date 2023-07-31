/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcheron <pcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 21:16:11 by pcheron           #+#    #+#             */
/*   Updated: 2023/07/26 21:16:41 by pcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	ft_get_time(long *time)
{
	struct timeval		time_val;

	if (gettimeofday(&time_val, NULL) < 0)
	{
		printf("Get time failed\n");
		return (false);
	}
	*time = (time_val.tv_sec * 1000000) + time_val.tv_usec;
	return (true);
}

// long	ft_clock(void)
// {
// 	struct timeval		time_val;

// 	gettimeofday(&time_val, NULL);
// 	return ((time_val.tv_sec * 1000000) + time_val.tv_usec);
// }

bool	ft_usleep(long time)
{
	long	end;
	long	start;

	if (!ft_get_time(&start))
		return (false);
	if (!ft_get_time(&end))
		return (false);
	while (end - start < time)
	{
		usleep(500);
		if (!ft_get_time(&end))
			return (false);
	}
	return (true);
}
