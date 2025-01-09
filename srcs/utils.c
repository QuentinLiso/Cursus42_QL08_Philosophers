/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qzoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:25:23 by qzoli             #+#    #+#             */
/*   Updated: 2025/01/09 13:25:24 by qzoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
		sign *= (*str++ - ',');
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

time_t	ft_get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1e3 + tv.tv_usec / 1e3);
}

void	ft_usleep(time_t time_in_ms)
{
	time_t	start_time_ms;

	start_time_ms = 0;
	start_time_ms = ft_get_time();
	while (ft_get_time() - start_time_ms < time_in_ms)
		usleep(100);
}

void	log_philo_status(t_philo *philo, char *msg)
{
	time_t	log_time_ms;

	log_time_ms = ft_get_time() - philo->dinner->start_time;
	pthread_mutex_lock(&philo->dinner->log_mtx);
	if (all_alive(philo))
		printf("%ld %d %s\n", log_time_ms, philo->seat, msg);
	pthread_mutex_unlock(&philo->dinner->log_mtx);
}

int	clear_mtx(t_dinner *dinner, t_philo (*p)[SIZE], t_fork (*f)[SIZE])
{
	int		i;
	t_philo	*buf_philos;
	t_fork	*buf_forks;

	i = -1;
	buf_philos = *p;
	buf_forks = *f;
	while (++i < dinner->philos)
	{
		pthread_mutex_destroy(&buf_philos[i].eat_last_mtx);
		pthread_mutex_destroy(&buf_forks[i].held_mtx);
	}
	pthread_mutex_destroy(&dinner->log_mtx);
	pthread_mutex_destroy(&dinner->dead_mtx);
	return (0);
}
