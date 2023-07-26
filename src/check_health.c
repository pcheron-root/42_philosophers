/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_health.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcheron <pcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:03:51 by pcheron           #+#    #+#             */
/*   Updated: 2023/07/26 21:04:15 by pcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	ft_are_they_satiated(t_table *table)
{
	int	i;

	if (table->nb_philo_must_eat >= 0)
	{
		i = 0;
		while (i < table->nb_philo)
		{
			pthread_mutex_lock(&((table->philo)[i].meals_m));
			if ((table->philo)[i].meals_v < table->nb_philo_must_eat)
			{
				pthread_mutex_unlock(&((table->philo)[i].meals_m));
				break ;
			}
			pthread_mutex_unlock(&((table->philo)[i].meals_m));
			i++;
		}
		if (i == table->nb_philo)
		{
			pthread_mutex_lock(&table->satiated_m);
			table->satiated_v = true;
			pthread_mutex_unlock(&table->satiated_m);
			return (true);
		}
	}
	return (false);
}

bool	ft_is_philo_alive(t_philo *philo)
{
	long	time;

	pthread_mutex_lock(&philo->last_meal_m);
	ft_get_time(&time);
	if (time - philo->last_meal_v >= philo->table->time_to_die)
		return (pthread_mutex_unlock(&philo->last_meal_m), false);
	pthread_mutex_unlock(&philo->last_meal_m);
	return (true);
}

bool	ft_are_they_alive(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		if (!ft_is_philo_alive(&table->philo[i]))
		{
			pthread_mutex_lock(&table->dead_m);
			table->dead_v = i;
			pthread_mutex_unlock(&table->dead_m);
			ft_print(&table->philo[table->dead_v], 4);
			return (false);
		}
		i++;
	}
	return (true);
}

void	ft_check_health(t_table *table)
{
	int		i;

	usleep(125);
	while (ft_are_they_alive(table) && !ft_are_they_satiated(table))
		usleep(125);
	i = 0;
	while (i < table->nb_philo)
	{
		pthread_join((table->spirit)[i], NULL);
		i++;
	}
}
