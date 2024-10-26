/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 18:47:10 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/26 16:49:44 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac == 5 || ac == 6)
	{
		if (parse_arg(av) == 1)
		{
			init_table(&table, av);
			create_philos(&table, av);
		}
		else
			return (ft_putstr_fd("Please enter valid arguments\n", 2), 1);
	}
	else
		return (ft_putstr_fd("Wrong number of arguments\n", 2), 1);
	return (0);
}
