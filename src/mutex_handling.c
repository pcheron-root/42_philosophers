/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcheron <pcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 19:32:40 by pcheron           #+#    #+#             */
/*   Updated: 2023/07/24 03:01:28 by pcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_destroy_mutex_tab(pthread_mutex_t *mutex, int max)
{
	int	i;

	i = 0;
	while (i < max)
	{
		pthread_mutex_destroy(mutex + i);
		i++;
	}
}

bool	ft_mutex_init(t_table *table)
{
	int	i;
	
	if (pthread_mutex_init(&table->print, NULL) < 0)
		return (false);
	if (pthread_mutex_init(&table->dead_m, NULL) < 0)
		return (false);
	if (pthread_mutex_init(&table->satiated_m, NULL) < 0)
		return (false);
	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&table->fork[i], NULL) < 0)
			return (ft_destroy_mutex_tab(table->fork, i), pthread_mutex_destroy(&table->print), false);
		if (pthread_mutex_init(&table->philo[i].meals_m, NULL) < 0)
			return (ft_destroy_mutex_tab(table->fork, i), pthread_mutex_destroy(&table->print), false);
		if (pthread_mutex_init(&table->philo[i].last_meal_m, NULL) < 0)
			return (ft_destroy_mutex_tab(table->fork, i), pthread_mutex_destroy(&table->print), false);
		i++;
	}
	return (true);
}
