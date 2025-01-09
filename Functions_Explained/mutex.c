#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

typedef struct s_data
{
	int				num;
	pthread_mutex_t	mutex;
} t_data;

t_data	*init_data()
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		exit (1);
	data->num = 0;
	pthread_mutex_init(&data->mutex, NULL);
	return (data);
}

void	free_data(t_data *data)
{
	pthread_mutex_destroy(&data->mutex);
	free(data);
}

void	exit_on_error(t_data *data, int exit_code)
{
	free_data(data);
	exit(exit_code);
}

void	*routine(void *arg)
{
	t_data	*data;
	int	i;

	data = (t_data *)arg;
	i = 0;
	while (i < 1000000)
	{
		pthread_mutex_lock(&data->mutex);
		(data->num)++;
		pthread_mutex_unlock(&data->mutex);
		i++;
	}
	return (NULL);
}

void	example()
{
	t_data		*data;
	pthread_t	t1;
	pthread_t	t2;

	data = init_data();
	if (pthread_create(&t1, NULL, &routine, data))
		exit_on_error(data, 2);
	if (pthread_create(&t2, NULL, &routine, data))
		exit_on_error(data, 2);
	
	if (pthread_join(t1, NULL))
		exit_on_error(data, 2);
	if (pthread_join(t2, NULL))
		exit_on_error(data, 2);
	
	printf("Num : %d\n", data->num);
	free_data(data);
}

int main()
{
	example();
	return (0);
}
