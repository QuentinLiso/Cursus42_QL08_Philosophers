#include "philo.h"

int main(int ac, char **av)
{
	t_dinner	dinner;
	t_philo		philos[SIZE];
	t_fork		forks[SIZE];

	if (init_dinner(&dinner, ac, av))
		return (EXIT_FAILURE);
	if (init_philo_fork(&dinner, &philos, &forks))
		return (EXIT_FAILURE);
	//test_init_dinner(&dinner);
	//test_init_pf(&dinner, philos);
	if (create_threads(&dinner, &philos))
		return (clear_mtx(&dinner, &philos, &forks));
	if (join_threads(&dinner, &philos))
		return (clear_mtx(&dinner, &philos, &forks));
	//test_all_graille(&dinner, philos);
	clear_mtx(&dinner, &philos, &forks);
	return (0);
}