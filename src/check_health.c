/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_health.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcheron <pcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:03:51 by pcheron           #+#    #+#             */
/*   Updated: 2023/07/24 17:53:51 by pcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// bool	ft_are_they_satiated(t_table *table)
// {
// 	pthread_mutex_lock(table->);
// 	if (->philos_finished_eat)
// 		return (true);
// 	pthread_mutex_unlock(table->);
// 	return (false);
// }

// bool	someone_die(t_philo *philos)
// {
// 	bool	value;

// 	pthread_mutex_lock(philos->args->m_dead);
// 	value = philos->args->philo_dead;
// 	pthread_mutex_unlock(philos->args->m_dead);
// 	return (value);
// }

// bool	ft_is_philo_alive(t_philo *philo)
// {
// 	long	time;

// 	pthread_mutex_lock(philo->table->last_meal_m);
// 	ft_get_time(&time);
// 	if (time - philo->last_meal_v >= philo->table->time_start)
// 		return (pthread_mutex_unlock(philo->table->last_meal_m), false);
// 	pthread_mutex_unlock(philo->table->last_meal_m);
// 	return (true);
// }

// bool	is_philo_finish(t_philo *philo)
// {
// 	bool	value;

// 	value = false;
// 	pthread_mutex_lock(philo->args->m_count_meals);
// 	if (philo->count_meals >= philo->args->min_meals
// 		&& philo->args->min_meals > 0)
// 		value = true;
// 	pthread_mutex_unlock(philo->args->m_count_meals);
// 	return (value);
// }

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
	// printf("wtf %ld et %ld enfin %ld\n", time, philo->last_meal_v, philo->table->time_to_die);
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
	{
		usleep(125);
		// i = 0;
		// while (i < table->nb_philo)
		// {
		// 	if (!ft_is_philo_alive(&(table->philo)[i]))
		// 	{
		// 		// dead msg
		// 		pthread_mutex_lock(table->dead_m);
		// 		table->dead_v = true;
		// 		pthread_mutex_unlock(table->dead_m);
		// 	}
		// 	else if (ft_are_they_satiated(table))
		// 	{
		// 		pthread_mutex_lock(table->satiated_m);
		// 		table->satiated_v = true;
		// 		pthread_mutex_unlock(table->satiated_m);
		// 	}
		// 	i++;
		// }
	}
	i = 0;
	pthread_mutex_lock(&table->dead_m);
	if (table->dead_v >= 0)
		ft_print(&table->philo[table->dead_v], 4);
	pthread_mutex_unlock(&table->dead_m);
	while (i < table->nb_philo)
	{
		pthread_join((table->spirit)[i], NULL);
		i++;
	}
	ft_table_clear(table);
}
