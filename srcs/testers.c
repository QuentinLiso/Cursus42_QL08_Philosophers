#include "philo.h"

void	test_init_dinner(t_dinner *dinner)
{
	printf("%d %ld %ld %ld %d\n",
		dinner->philos,
		dinner->tt_die,
		dinner->tt_eat,
		dinner->tt_sleep,
		dinner->eat_max);
}

void	test_init_pf(t_dinner *dinner, t_philo philos[SIZE])
{
	int	i;

	i = -1;
	while (++i < dinner->philos)
	{
		printf("Philo[%d] : Seat %d (%d) Left fork %d Right fork : %d\n",
			i,
			philos[i].seat,
			philos[i].even_seat,
			philos[i].l_fork->id,
			philos[i].r_fork->id);
	}
}

void	test_all_graille(t_dinner *dinner, t_philo philos[SIZE])
{
	int	i;

	i = -1;
	while (++i < dinner->philos)
	{
		if (philos[i].eat_count != dinner->eat_max)
		{
			printf("Tlm n'a pas graille.\n");
			return ;
		}
	}
	printf("Tlm a graille comme des gros sacs.\n");
}