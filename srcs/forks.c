#include "philo.h"

void	take_l_fork(t_philo *philo)
{
	if (all_alive(philo))
	{
		pthread_mutex_lock(&philo->l_fork->held_mtx);
		if (!philo->l_fork_held && !philo->l_fork->held)
		{
			philo->l_fork_held = true;
			philo->l_fork->held = true;
			log_philo_status(philo, TAKING_FORK);
		}
		pthread_mutex_unlock(&philo->l_fork->held_mtx);
	}
}

void	take_r_fork(t_philo *philo)
{
	if (all_alive(philo))
	{
		pthread_mutex_lock(&philo->r_fork->held_mtx);
		if (!philo->r_fork_held && !philo->r_fork->held)
		{
			philo->r_fork_held = true;
			philo->r_fork->held = true;
			log_philo_status(philo, TAKING_FORK);
		}
		pthread_mutex_unlock(&philo->r_fork->held_mtx);
	}
}

void	put_l_fork(t_philo *philo)
{
	if (all_alive(philo))
	{
		pthread_mutex_lock(&philo->l_fork->held_mtx);
		philo->l_fork_held = false;
		philo->l_fork->held = false;
		pthread_mutex_unlock(&philo->l_fork->held_mtx);
	}
}

void	put_r_fork(t_philo *philo)
{
	if (all_alive(philo))
	{
		pthread_mutex_lock(&philo->r_fork->held_mtx);
		philo->r_fork_held = false;
		philo->r_fork->held = false;
		pthread_mutex_unlock(&philo->r_fork->held_mtx);
	}
}