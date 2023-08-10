/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcheron <pcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 19:32:40 by pcheron           #+#    #+#             */
/*   Updated: 2023/08/10 20:29:44 by pcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_destroy_all_mutex(t_table *table, int i, int j, int k)
{
	int	l;

	l = 0;
	while (l < i)
	{
		pthread_mutex_destroy(table->fork + l);
		l++;
	}
	l = 0;
	while (l < j)
	{
		pthread_mutex_destroy(&table->philo[l].meals_m);
		l++;
	}
	l = 0;
	while (l < k)
	{
		pthread_mutex_destroy(&table->philo[l].last_meal_m);
		l++;
	}
	pthread_mutex_destroy(&table->print_m);
	pthread_mutex_destroy(&table->dead_m);
	pthread_mutex_destroy(&table->satiated_m);
}

bool	ft_mutex_init(t_table *table)
{
	int	i;

	if (pthread_mutex_init(&table->print_m, NULL) < 0)
		return (false);
	if (pthread_mutex_init(&table->dead_m, NULL) < 0)
		return (pthread_mutex_destroy(&table->print_m), false);
	if (pthread_mutex_init(&table->satiated_m, NULL) < 0)
		return (pthread_mutex_destroy(&table->print_m),
			pthread_mutex_destroy(&table->dead_m), false);
	i = 0;
	while (i < table->nb_philo)
	{
		if (pthread_mutex_init(&table->fork[i], NULL) < 0)
			return (ft_destroy_all_mutex(table, i, i, i), false);
		if (pthread_mutex_init(&table->philo[i].meals_m, NULL) < 0)
			return (ft_destroy_all_mutex(table, i + 1, i, i), false);
		if (pthread_mutex_init(&table->philo[i].last_meal_m, NULL) < 0)
			return (ft_destroy_all_mutex(table, i + 1, i + 1, i), false);
		i++;
	}
	return (true);
}
