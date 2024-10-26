/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_brother.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 17:14:36 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/26 20:59:04 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	time_diff(t_philo *ptr)
{
	return (get_time() - ptr->table->start_time);
}

int	check_isfull(t_table *table, int goalmeal)
{
	if (goalmeal == table->nb_philo)
	{
		pthread_mutex_lock(&table->death_mutex);
		table->end_flag = 1;
		pthread_mutex_unlock(&table->death_mutex);
		return (1);
	}
	return (0);
}

int	check_isdead(t_philo *philo, t_table *table)
{
	long	current_time;
	long	last_meal_time;

	current_time = time_diff(philo);
	pthread_mutex_lock(philo->meal_mutex);
	last_meal_time = philo->last_meal;
	pthread_mutex_unlock(philo->meal_mutex);
	if (current_time - last_meal_time > philo->d_time)
	{
		print_routine(philo, 4);
		pthread_mutex_lock(&table->death_mutex);
		table->end_flag = 1;
		pthread_mutex_unlock(&table->death_mutex);
		return (1);
	}
	return (0);
}

void	big_brother(t_table *table)
{
	int		i;
	int		goalmeal;
	t_philo	*philo;

	while (1)
	{
		i = -1;
		goalmeal = 0;
		while (++i < table->nb_philo)
		{
			philo = &table->philo[i];
			if (check_isdead(philo, table))
				return ;
			pthread_mutex_lock(&table->meal_mutex);
			if (table->meal_max && philo->meal == table->meal_max)
				goalmeal++;
			pthread_mutex_unlock(&table->meal_mutex);
		}
		if (check_isfull(table, goalmeal))
			return ;
		usleep(100);
	}
}
