/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcheron <pcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:50:57 by pcheron           #+#    #+#             */
/*   Updated: 2023/07/26 21:35:00 by pcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	ft_parse(char **argv, t_table *table)
{
	if (!ft_atoi(&table->nb_philo, argv[1]) || table->nb_philo <= 0)
		return (false);
	if (!ft_atol(&table->time_to_die, argv[2]) || table->time_to_die < 0)
		return (false);
	if (!ft_atol(&table->time_to_eat, argv[3]) || table->time_to_eat < 0)
		return (false);
	if (!ft_atol(&table->time_to_sleep, argv[4]) || table->time_to_sleep < 0)
		return (false);
	if (argv[5])
	{
		if (!ft_atoi(&table->nb_philo_must_eat, argv[5])
			|| table->nb_philo_must_eat < 0)
			return (false);
	}
	else
		table->nb_philo_must_eat = -1;
	table->time_to_die *= 1000;
	table->time_to_eat *= 1000;
	table->time_to_sleep *= 1000;
	if (table->time_to_die < 0 || table->time_to_eat < 0
		|| table->time_to_sleep < 0)
		return (false);
	table->dead_v = -1;
	table->satiated_v = false;
	return (true);
}

static void	ft_philo_init(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		(table->philo)[i].id = i;
		(table->philo)[i].meals_v = 0;
		(table->philo)[i].left_fork = &table->fork[i];
		(table->philo)[i].right_fork = &table->fork[(i + 1) % table->nb_philo];
		(table->philo)[i].table = table;
		i++;
	}
}

bool	ft_run_threads(t_table *table)
{
	int	i;

	i = 0;
	ft_get_time(&table->time_start);
	while (i < table->nb_philo)
	{
		ft_get_time(&(table->philo)[i].last_meal_v);
		if (pthread_create(&(table->spirit)[i], NULL,
			(void *)ft_philo_lifestyle, &(table->philo[i])))
		{
			while (i > 0)
			{
				i--;
				pthread_join((table->spirit)[i], NULL);
			}
			return (false);
		}
		i++;
	}
	return (true);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc < 5 || argc > 6 || !ft_parse(argv, &table))
		return (write(2, SYNTAX, 84), 1);
	if (!ft_table_init(&table))
		return (write(2, "allocation failed\n", 19), 1);
	ft_philo_init(&table);
	if (!ft_mutex_init(&table))
		return (write(2, "init mutex failed\n", 19), ft_table_clear(&table), 1);
	if (!ft_run_threads(&table))
		return (write(2, "run thread failed\n", 19), ft_clear_all(&table), 1);
	ft_check_health(&table);
	ft_clear_all(&table);
}
