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
	return (ret);
}

void	*routine_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!philo->even_seat)
		ft_usleep(1);
	while (all_alive(philo))
	{
		if (philo->eat_count >= philo->dinner->eat_max)
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
	ft_usleep(philo->dinner->tt_eat);
	philo->eat_count++;
	pthread_mutex_lock(&philo->eat_last_mtx);
	philo->eat_last = ft_get_time() - philo->dinner->start_time;
	pthread_mutex_unlock(&philo->eat_last_mtx);
	put_l_fork(philo);
	put_r_fork(philo);
	log_philo_status(philo, SLEEPING);
	ft_usleep(philo->dinner->tt_sleep);
	log_philo_status(philo, THINKING);
}
