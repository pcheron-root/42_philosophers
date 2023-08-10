/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifestyle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcheron <pcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:09:14 by pcheron           #+#    #+#             */
/*   Updated: 2023/08/10 20:42:41 by pcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	ft_handle_direction_lock(t_philo *philo)
{
	if (philo->id & 1)
	{
		pthread_mutex_lock(philo->left_fork);
		if (!ft_print(philo, 3))
			return (pthread_mutex_unlock(philo->left_fork), false);
		pthread_mutex_lock(philo->right_fork);
		if (!ft_print(philo, 3))
			return (pthread_mutex_unlock(philo->left_fork),
				pthread_mutex_unlock(philo->right_fork), false);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		if (!ft_print(philo, 3))
			return (pthread_mutex_unlock(philo->right_fork), false);
		pthread_mutex_lock(philo->left_fork);
		if (!ft_print(philo, 3))
			return (pthread_mutex_unlock(philo->left_fork),
				pthread_mutex_unlock(philo->right_fork), false);
	}
	return (true);
}

bool	ft_eat(t_philo *philo)
{
	if (!ft_handle_direction_lock(philo))
		return (false);
	if (!ft_print(philo, 0))
		return (pthread_mutex_unlock(philo->right_fork),
			pthread_mutex_unlock(philo->left_fork), false);
	pthread_mutex_lock(&philo->last_meal_m);
	ft_get_time(&philo->last_meal_v);
	pthread_mutex_unlock(&philo->last_meal_m);
	ft_usleep(philo->table->time_to_eat);
	pthread_mutex_lock(&philo->meals_m);
	philo->meals_v++;
	pthread_mutex_unlock(&philo->meals_m);
	if (philo->id & 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
	}
	return (true);
}

bool	ft_sleep(t_philo *philo)
{
	if (!ft_print(philo, 1))
		return (false);
	ft_usleep(philo->table->time_to_sleep);
	return (true);
}

bool	ft_memento_mori(t_table *table)
{
	pthread_mutex_lock(&table->dead_m);
	if (table->dead_v >= 0)
		return (pthread_mutex_unlock(&table->dead_m), false);
	pthread_mutex_unlock(&table->dead_m);
	pthread_mutex_lock(&table->satiated_m);
	if (table->satiated_v)
		return (pthread_mutex_unlock(&table->satiated_m), false);
	pthread_mutex_unlock(&table->satiated_m);
	return (true);
}

void	*ft_philo_lifestyle(t_philo *philo)
{
	if (philo->table->nb_philo == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		ft_print(philo, 3);
		while (ft_memento_mori(philo->table))
			ft_usleep(125);
		pthread_mutex_unlock(philo->left_fork);
		return (NULL);
	}
	while (ft_memento_mori(philo->table))
	{
		if (!(philo->id & 1))
			ft_usleep(500);
		if (!ft_eat(philo))
			break ;
		if (!ft_sleep(philo))
			break ;
		ft_usleep((philo->table->time_to_eat > philo->table->time_to_sleep)
			* (philo->table->time_to_eat - philo->table->time_to_sleep) + 125);
		if (!ft_print(philo, 2))
			break ;
	}
	return (NULL);
}
