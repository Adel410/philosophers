/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 14:28:34 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/17 12:50:27 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	parse_arg(char **av)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (av[i] && ft_atoi(av[i]) > 200)
		return (0);
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (ft_isdigit(av[i][j]) == 0)
				return (0);
			j++;
		}
		if (i < 5 && ft_atoi(av[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
