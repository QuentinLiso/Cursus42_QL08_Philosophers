/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qzoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:24:32 by qzoli             #+#    #+#             */
/*   Updated: 2025/01/09 13:24:33 by qzoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_death(void *arg)
{
	int			i;
	t_philo		*buf_philos;
	t_dinner	*dinner;
	time_t		current_time;

	buf_philos = *(t_philo (*)[200])arg;
	dinner = buf_philos[0].dinner;
	while (1)
	{
		i = -1;
		current_time = ft_get_time() - dinner->start_time;
		while (++i < dinner->philos)
		{
			if (is_dead(&buf_philos[i], current_time))
				return (NULL);
		}
		ft_usleep(1);
	}
	return (NULL);
}

bool	is_dead(t_philo *philo, time_t current_time)
{
	time_t		elapsed;
	t_dinner	*dinner;

	dinner = philo->dinner;
	pthread_mutex_lock(&philo->eat_last_mtx);
	elapsed = current_time - philo->eat_last;
	pthread_mutex_unlock(&philo->eat_last_mtx);
	if (elapsed > dinner->tt_die)
	{
		pthread_mutex_lock(&dinner->log_mtx);
		pthread_mutex_lock(&dinner->dead_mtx);
		dinner->any_dead = true;
		pthread_mutex_unlock(&dinner->dead_mtx);
		printf("%ld %d %s\n", current_time, philo->seat, DIED);
		pthread_mutex_unlock(&dinner->log_mtx);
		return (true);
	}
	return (false);
}

bool	all_alive(t_philo *philo)
{
	bool	ret;

	pthread_mutex_lock(&philo->dinner->dead_mtx);
	ret = !philo->dinner->any_dead;
	pthread_mutex_unlock(&philo->dinner->dead_mtx);
	return (ret);
}
