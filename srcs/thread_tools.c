/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 16:45:55 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/26 21:07:20 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_flags(t_philo *ptr)
{
	int	flag;

	pthread_mutex_lock(ptr->death_mutex);
	flag = ptr->table->end_flag;
	pthread_mutex_unlock(ptr->death_mutex);
	return (flag);
}

void	take_forks(t_philo *ptr)
{
	if (ptr->nb_philo > 1)
	{
		if (ptr->id % 2)
		{
			pthread_mutex_lock(ptr->fork_left);
			pthread_mutex_lock(ptr->fork_right);
		}
		else
		{
			pthread_mutex_lock(ptr->fork_right);
			pthread_mutex_lock(ptr->fork_left);
		}
	}
	else
		pthread_mutex_lock(ptr->fork_left);
}

void	drop_forks(t_philo *ptr)
{
	if (ptr->nb_philo > 1)
	{
		pthread_mutex_unlock(ptr->fork_left);
		pthread_mutex_unlock(ptr->fork_right);
	}
	else
		pthread_mutex_unlock(ptr->fork_left);
}

long	get_time(void)
{
	struct timeval	tv;
	long			value;

	gettimeofday(&tv, NULL);
	value = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (value);
}

void	better_sleep(long duration, t_philo *philo)
{
	long	start_time;

	start_time = get_time();
	while ((get_time() - start_time) < duration)
	{
		if (check_flags(philo))
			break ;
		usleep(50);
	}
}
