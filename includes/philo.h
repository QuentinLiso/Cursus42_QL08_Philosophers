/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qzoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 13:24:58 by qzoli             #+#    #+#             */
/*   Updated: 2025/01/09 13:24:59 by qzoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <unistd.h>
# include <limits.h>
# include <time.h>
# include <sys/time.h>
# include <pthread.h>

# define SIZE 200
# define EATING "is eating"
# define TAKING_FORK "has taken a fork"
# define SLEEPING "is sleeping"
# define THINKING "is thinking"
# define DIED "died"
# define FULL "is full ce gros porc"

typedef pthread_mutex_t	t_mtx;

typedef struct s_dinner
{
	int			philos;
	time_t		tt_die;
	time_t		tt_eat;
	time_t		tt_sleep;
	int			eat_max;
	int			graille_count;
	t_mtx		graille_mtx;
	time_t		start_time;
	t_mtx		log_mtx;
	bool		any_dead;
	t_mtx		dead_mtx;
	pthread_t	death_th;
}	t_dinner;

typedef struct s_fork
{
	int		id;
	bool	held;
	t_mtx	held_mtx;
}	t_fork;

typedef struct s_philo
{
	pthread_t	th;
	int			seat;
	bool		even_seat;
	time_t		eat_last;
	t_mtx		eat_last_mtx;
	int			eat_count;
	bool		is_full;
	t_fork		*r_fork;
	bool		r_fork_held;
	t_fork		*l_fork;
	bool		l_fork_held;
	t_dinner	*dinner;
}	t_philo;

// Init.c
int		init_dinner(t_dinner *dinner, int ac, char **av);
int		init_philo_fork(t_dinner *dinner, t_philo (*p)[SIZE],
			t_fork (*f)[SIZE]);
void	set_philo(t_philo *philo, int i);

// Threads.c
int		create_threads(t_dinner *dinner, t_philo (*philos)[SIZE]);
int		join_threads(t_dinner *dinner, t_philo (*philos)[SIZE]);

// Graille.c
void	*routine_philo(void *arg);
void	eat_sleep_think(t_philo *philo);
bool	all_graille(t_dinner *dinner);

// Forks.c
void	take_l_fork(t_philo *philo);
void	take_r_fork(t_philo *philo);
void	put_l_fork(t_philo *philo);
void	put_r_fork(t_philo *philo);

// Death.c
void	*routine_death(void *arg);
bool	is_dead(t_philo *philo, time_t current_time);
bool	all_alive(t_philo *philo);

// Utils.c
int		ft_atoi(char *str);
time_t	ft_get_time(void);
void	ft_usleep(time_t time_in_ms);
void	log_philo_status(t_philo *philo, char *msg);
int		clear_mtx(t_dinner *dinner, t_philo (*p)[SIZE], t_fork (*f)[SIZE]);

// Testers.c
void	test_init_dinner(t_dinner *dinner);
void	test_init_pf(t_dinner *dinner, t_philo philos[SIZE]);
void	test_all_graille(t_dinner *dinner, t_philo philos[SIZE]);

#endif
