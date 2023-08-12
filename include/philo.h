/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcheron <pcheron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 23:44:43 by pcheron           #+#    #+#             */
/*   Updated: 2023/08/12 13:29:24 by pcheron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <string.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

	// pthread_t		*spirit;
	// bool			alive_v;
	// pthread_mutex_t	alive_m;
typedef struct s_philo
{
	int				id;
	struct s_table	*table;
	int				meals_v;
	pthread_mutex_t	meals_m;
	long			last_meal_v;
	pthread_mutex_t	last_meal_m;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

typedef struct s_table
{
	int				nb_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_start;
	int				nb_philo_must_eat;
	bool			satiated_v;
	pthread_mutex_t	satiated_m;
	int				dead_v;
	pthread_mutex_t	dead_m;
	pthread_t		*spirit;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print_m;
}	t_table;

# define SYNTAX "./philo <nb_philo> \
<time_to_die> <time_to_eat> <time_to_sleep> <nb_philo_must_eat>\n"

// libft
bool	ft_atoi(int *result, char *str);
bool	ft_atol(long *result, char *str);
bool	ft_print(t_philo *philo, int option);

// time
bool	ft_usleep(long time);
bool	ft_get_time(long *time);
long	ft_clock(void);

// lifestyle
void	*ft_philo_lifestyle(t_philo *philo);

// is it dusk ?
void	ft_check_health(t_table *table);

// philo lifestyle
void	*ft_philo_lifestyle(t_philo *philo);
bool	ft_memento_mori(t_table *table);

// mutex handling
bool	ft_mutex_init(t_table *table);
void	ft_destroy_all_mutex(t_table *table, int i, int j, int k);

// structure
bool	ft_table_init(t_table *table);
void	ft_table_clear(t_table *table);
void	ft_clear_all(t_table *table);

#endif