/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 21:04:48 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/26 21:07:10 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_routine(t_philo *philo, int i)
{
	long	current_time;

	pthread_mutex_lock(philo->print_mutex);
	if (!check_flags(philo))
	{
		current_time = time_diff(philo);
		if (i == 1)
		{
			current_time = time_diff(philo);
			printf("%ld %d has taken a fork\n", current_time, philo->id);
			printf("%ld %d has taken a fork\n", current_time, philo->id);
			printf("%ld %d is eating\n", current_time, philo->id);
		}
		else if (i == 2)
			printf("%ld %d is sleeping\n", current_time, philo->id);
		else if (i == 3)
			printf("%ld %d is thinking\n", current_time, philo->id);
		else if (i == 4)
			printf("%ld %d died\n", current_time, philo->id);
	}
	pthread_mutex_unlock(philo->print_mutex);
}

void	eating(t_philo *philo)
{
	take_forks(philo);
	if (!check_flags(philo))
	{
		pthread_mutex_lock(philo->meal_mutex);
		philo->last_meal = time_diff(philo);
		pthread_mutex_unlock(philo->meal_mutex);
		print_routine(philo, 1);
		pthread_mutex_lock(philo->meal_mutex);
		philo->meal++;
		pthread_mutex_unlock(philo->meal_mutex);
		better_sleep(philo->e_time, philo);
	}
	drop_forks(philo);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (get_time() < philo->table->start_time)
		usleep(50);
	while (!check_flags(philo))
	{
		if (philo->id % 2 == 0)
			usleep(100);
		eating(philo);
		if (check_flags(philo))
			break ;
		print_routine(philo, 2);
		better_sleep(philo->s_time, philo);
		if (check_flags(philo))
			break ;
		print_routine(philo, 3);
	}
	return (NULL);
}

void	solo_philo(t_philo *philo)
{
	long	current_time;

	philo->last_meal = time_diff(philo);
	current_time = time_diff(philo);
	usleep((philo->d_time) * 1000);
	printf("%ld %d has taken a fork\n", current_time, philo->id);
	print_routine(philo, 4);
}

void	create_philos(t_table *table, char **av)
{
	int		i;
	t_philo	*philo;

	philo = ft_calloc(sizeof(t_philo), table->nb_philo);
	table->philo = philo;
	i = -1;
	while (++i < table->nb_philo)
		init_philos(&philo[i], table, av, i);
	i = -1;
	if (table->nb_philo == 1)
	{
		solo_philo(&philo[0]);
		return ;
	}
	while (++i < table->nb_philo)
	{
		if (pthread_create(&table->thread[i], NULL, routine,
				(void *)&philo[i]) != 0)
		{
			ft_putstr_fd("pthread_create failed\n", 2);
			break ;
		}
	}
	big_brother(table);
	cleanup(philo, table);
}
