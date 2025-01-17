/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qzoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:24:48 by qzoli             #+#    #+#             */
/*   Updated: 2025/01/09 13:24:49 by qzoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_dinner	dinner;
	t_philo		philos[SIZE];
	t_fork		forks[SIZE];

	if (init_dinner(&dinner, ac, av))
		return (EXIT_FAILURE);
	if (init_philo_fork(&dinner, &philos, &forks))
		return (EXIT_FAILURE);
	if (create_threads(&dinner, &philos))
		return (clear_mtx(&dinner, &philos, &forks));
	if (join_threads(&dinner, &philos))
		return (clear_mtx(&dinner, &philos, &forks));
	clear_mtx(&dinner, &philos, &forks);
	return (0);
}
