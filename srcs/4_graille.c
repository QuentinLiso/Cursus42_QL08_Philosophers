/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graille.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qliso <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 17:02:34 by qliso             #+#    #+#             */
/*   Updated: 2025/01/17 17:02:36 by qliso            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!philo->even_seat)
		ft_usleep(100);
	while (all_alive(philo))
	{
		if (philo->is_full)
			break ;
		pthread_mutex_lock(&philo->dinner->dead_mtx);
		if (philo->dinner->any_dead)
		{
			pthread_mutex_unlock(&philo->dinner->dead_mtx);
			break ;
		}
		pthread_mutex_unlock(&philo->dinner->dead_mtx);
		take_l_fork(philo);
		if (philo->l_fork_held)
			take_r_fork(philo);
		if (philo->l_fork_held && philo->r_fork_held)
			eat_sleep_think(philo);
	}
	return (NULL);
}

void	eat_sleep_think(t_philo *philo)
{
	log_philo_status(philo, EATING);
	pthread_mutex_lock(&philo->eat_last_mtx);
	philo->eat_last = ft_get_time() - philo->dinner->start_time;
	pthread_mutex_unlock(&philo->eat_last_mtx);
	ft_usleep(philo->dinner->tt_eat);
	philo->eat_count++;
	put_l_fork(philo);
	put_r_fork(philo);
	if (philo->eat_count >= philo->dinner->eat_max)
	{
		pthread_mutex_lock(&philo->dinner->graille_mtx);
		philo->dinner->graille_count--;
		pthread_mutex_unlock(&philo->dinner->graille_mtx);
		philo->is_full = true;
		return ;
	}
	log_philo_status(philo, SLEEPING);
	ft_usleep(philo->dinner->tt_sleep);
	log_philo_status(philo, THINKING);
}

bool	all_graille(t_dinner *dinner)
{
	bool	ret;

	pthread_mutex_lock(&dinner->graille_mtx);
	if (dinner->graille_count > 0)
		ret = false;
	else
		ret = true;
	pthread_mutex_unlock(&dinner->graille_mtx);
	return (ret);
}
