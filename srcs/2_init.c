/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qzoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:24:42 by qzoli             #+#    #+#             */
/*   Updated: 2025/01/09 13:24:43 by qzoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_dinner(t_dinner *dinner, int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		printf("Wrong args!\n");
		return (1);
	}
	dinner->philos = ft_atoi(av[1]);
	dinner->tt_die = ft_atoi(av[2]);
	dinner->tt_eat = ft_atoi(av[3]);
	dinner->tt_sleep = ft_atoi(av[4]);
	dinner->eat_max = INT_MAX;
	if (ac == 6)
	{
		dinner->eat_max = ft_atoi(av[5]);
		if (dinner->eat_max < 0)
			return (1);
	}
	dinner->any_dead = false;
	if (dinner->philos <= 0 || dinner->philos > 200 || dinner->tt_die < 0
		|| dinner->tt_eat < 0 || dinner->tt_sleep < 0)
		return (1);
	dinner->graille_count = dinner->philos;
	pthread_mutex_init(&dinner->graille_mtx, NULL);
	pthread_mutex_init(&dinner->log_mtx, NULL);
	pthread_mutex_init(&dinner->dead_mtx, NULL);
	return (0);
}

int	init_philo_fork(t_dinner *dinner, t_philo (*p)[SIZE], t_fork (*f)[SIZE])
{
	t_philo	*buf_philos;
	t_fork	*buf_forks;
	int		i;

	buf_philos = *p;
	buf_forks = *f;
	i = -1;
	while (++i < dinner->philos)
	{
		set_philo(&buf_philos[i], i);
		buf_philos[i].l_fork = &buf_forks[(i + 1) % dinner->philos];
		buf_philos[i].r_fork = &buf_forks[i];
		buf_philos[i].dinner = dinner;
		if (pthread_mutex_init(&buf_philos[i].eat_last_mtx, NULL))
			return (1);
		buf_forks[i].id = i;
		buf_forks[i].held = false;
		if (pthread_mutex_init(&buf_forks[i].held_mtx, NULL))
			return (1);
	}
	return (0);
}

void	set_philo(t_philo *philo, int i)
{
	philo->seat = i + 1;
	philo->even_seat = (bool)(i % 2);
	philo->eat_count = 0;
	philo->eat_last = 0;
	philo->is_full = false;
	philo->l_fork_held = false;
	philo->r_fork_held = false;
}
