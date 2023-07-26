/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcheron <pcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 20:55:57 by pcheron           #+#    #+#             */
/*   Updated: 2023/07/26 21:04:29 by pcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_table_clear(t_table *table)
{
	free(table->philo);
	free(table->spirit);
	free(table->fork);
}

void	ft_clear_all(t_table *table)
{
	ft_destroy_all_mutex(table, table->nb_philo, table->nb_philo,
		table->nb_philo);
	ft_table_clear(table);
}

bool	ft_table_init(t_table *table)
{
	table->spirit = malloc(sizeof(pthread_t) * table->nb_philo);
	if (!table->spirit)
		return (false);
	table->philo = malloc(sizeof(t_philo) * table->nb_philo);
	if (!table->philo)
		return (free(table->spirit), false);
	table->fork = malloc(sizeof(pthread_mutex_t) * table->nb_philo);
	if (!table->fork)
		return (free(table->philo), free(table->spirit), false);
	return (true);
}
