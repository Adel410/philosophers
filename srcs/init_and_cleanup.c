/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_and_cleanup.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/18 20:46:08 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/26 21:03:08 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	init_table(t_table *table, char **av)
{
	int	i;

	i = -1;
	table->end_flag = 0;
	table->nb_philo = ft_atoi(av[1]);
	if (av[5])
		table->meal_max = ft_atoi(av[5]);
	else
		table->meal_max = 0;
	table->start_time = get_time();
	table->thread = ft_calloc(sizeof(pthread_t), table->nb_philo);
	table->fork = ft_calloc(sizeof(pthread_mutex_t), table->nb_philo);
	while (++i < table->nb_philo)
		pthread_mutex_init(&table->fork[i], NULL);
	pthread_mutex_init(&table->death_mutex, NULL);
	pthread_mutex_init(&table->meal_mutex, NULL);
	pthread_mutex_init(&table->print_mutex, NULL);
	pthread_mutex_init(&table->check_mutex, NULL);
}

void	init_philos(t_philo *philo, t_table *table, char **av, int i)
{
	philo->table = table;
	philo->id = i + 1;
	philo->meal = 0;
	philo->last_meal = table->start_time;
	philo->d_time = ft_atoi(av[2]);
	philo->e_time = ft_atoi(av[3]);
	philo->s_time = ft_atoi(av[4]);
	philo->nb_philo = table->nb_philo;
	philo->fork_left = &table->fork[i];
	philo->fork_right = &table->fork[(i + 1) % table->nb_philo];
	philo->death_mutex = &table->death_mutex;
	philo->meal_mutex = &table->meal_mutex;
	philo->print_mutex = &table->print_mutex;
	philo->check_mutex = &table->check_mutex;
}

void	destroy_mutex(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&table->death_mutex);
	pthread_mutex_destroy(&table->meal_mutex);
	pthread_mutex_destroy(&table->print_mutex);
	pthread_mutex_destroy(&table->check_mutex);
	while (i < table->nb_philo)
	{
		pthread_mutex_destroy(&table->fork[i]);
		i++;
	}
}

void	join_thread(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->nb_philo)
	{
		pthread_join(table->thread[i], NULL);
		i++;
	}
}

void	cleanup(t_philo *ptr, t_table *table)
{
	join_thread(table);
	destroy_mutex(table);
	free(ptr);
	free(table->fork);
	free(table->thread);
}
