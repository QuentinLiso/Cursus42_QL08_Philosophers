/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qzoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:25:10 by qzoli             #+#    #+#             */
/*   Updated: 2025/01/09 13:25:11 by qzoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_threads(t_dinner *dinner, t_philo (*philos)[SIZE])
{
	int		i;
	t_philo	*buf_philo;

	i = -1;
	buf_philo = *philos;
	dinner->start_time = ft_get_time();
	while (++i < dinner->philos)
	{
		if (pthread_create(&(buf_philo[i].th), NULL, &routine_philo,
				&buf_philo[i]))
			return (1);
	}
	if (pthread_create(&(dinner->death_th), NULL, &routine_death, philos))
		return (1);
	return (0);
}

int	join_threads(t_dinner *dinner, t_philo (*philos)[SIZE])
{
	int		i;
	t_philo	*buf_philo;
	int		ret;

	i = -1;
	buf_philo = *philos;
	ret = 0;
	while (++i < dinner->philos)
		if (pthread_join(buf_philo[i].th, NULL))
			ret = 1;
	if (pthread_join(dinner->death_th, NULL))
		ret = 1;
	return (ret);
}
