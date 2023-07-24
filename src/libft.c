/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcheron <pcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 18:04:00 by pcheron           #+#    #+#             */
/*   Updated: 2023/07/24 18:11:38 by pcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	ft_atoi(int *result, char *str)
{
	int	i;
	int	sign;

	sign = 1;
	i = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	*result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (*result > *result * 10 + str[i] - 48)
			return (false);
		*result = *result * 10 + str[i] - 48;
		i++;
	}
	*result *= sign;
	return (true);
}

bool	ft_atol(long *result, char *str)
{
	int	i;
	int	sign;

	sign = 1;
	i = 0;
	while ((str[i] > 8 && str[i] < 14) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	*result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (*result > *result * 10 + str[i] - 48)
			return (false);
		*result = *result * 10 + str[i] - 48;
		i++;
	}
	*result *= sign;
	return (true);
}

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

long	ft_clock(void)
{
	struct timeval		time_val;

	gettimeofday(&time_val, NULL);
	return ((time_val.tv_sec * 1000000) + time_val.tv_usec);
}

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

// 0 eat
// 1 sleep
// 2 thinking
// 3 fork
// 4 dead
bool	ft_print(t_philo *philo, int option)
{
	static char *lookup[5] = {
		"%ld %d is eating\n",
		"%ld %d is sleeping\n",
		"%ld %d is thinking\n",
		"%ld %d has taken a fork\n",
		"%ld %d died\n"};

	pthread_mutex_lock(&philo->table->print);
	if (option != 4 && !ft_memento_mori(philo->table))
		return (pthread_mutex_unlock(&philo->table->print), false);
	printf(lookup[option], (ft_clock() - philo->table->time_start) / 1000, philo->id + 1);
	pthread_mutex_unlock(&philo->table->print);
	return (true);
}
	// {
	// }
		// printf("wtf %ld et %ld\n", ft_clock(), philo->table->time_start);
