#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/types.h>


//		========== How to pass arguments to threads ==========
typedef struct s_data
{
	int			pos;
	pthread_t	th;
}	t_data;

int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

void	*routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	printf("philo %d\n", data->pos);
//	free(arg);
	return (NULL);
}

void create_thread(t_data **data)
{
	int i;
	for (i = 0; i < 10; i++)
	{
		if (pthread_create(&((*data)[i].th), NULL, &routine, &((*data)[i])))
			perror("Failed to create thread");
	}
}


int main()
{
	t_data	*data;

	data = calloc (10, sizeof(t_data));
	int	i;
	for (i = 0; i < 10; i++)
		data[i].pos = i;
	create_thread(&data);
	for (i = 0; i < 10; i++)
	{
		if (pthread_join(data[i].th, NULL))
			perror("Failed to join thread");
	}
}



//		========== Practical example for using threads ==========
// int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

// void	*routine(void *arg)
// {
// 	int index = *(int *)arg;
// 	int	sum = 0;
// 	for (int j = 0; j < 5; j++)
// 		sum += primes[index + j];
// 	printf("Local sum : %d\n", sum);
// 	*(int *)arg = sum;
// 	return(arg);
// }

// int main()
// {
// 	pthread_t th[2];
// 	int	i;
// 	for (i = 0; i < 2; i++)
// 	{
// 		int	*a = malloc(sizeof(int));
// 		*a = i * 5;
// 		if (pthread_create(th + i, NULL, &routine, a))
// 			perror("Failed to create thread");
// 	}
// 	int globalSum = 0;
// 	for (i = 0; i < 2; i++)
// 	{
// 		int	*r;
// 		if (pthread_join(th[i], (void **)&r))
// 			perror("Failed to join thread");
// 		globalSum += *r;
// 		free(r);
// 	}
// 	printf("Global sum : %d\n", globalSum);
// 	return (0);
// }

//		========== How to pass arguments to threads ==========
// int primes[10] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29 };

// void	*routine(void *arg)
// {
// 	sleep(1);
// 	int index = *(int *)arg;
// 	printf("%d ", primes[index]);
// 	free(arg);
// 	return (NULL);
// }

// int main()
// {
// 	pthread_t th[10];
// 	int	i;
// 	for (i = 0; i < 10; i++)
// 	{
// 		int	*a = malloc(sizeof(int));
// 		*a = i;
// 		if (pthread_create(th + i, NULL, &routine, a))
// 			perror("Failed to create thread");
// 	}
// 	for (i = 0; i < 10; i++)
// 	{
// 		if (pthread_join(th[i], NULL))
// 			perror("Failed to join thread");
// 	}
// }


//		========== Get return value from a thread ==========
// void	*roll_dice()
// {
// 	int value = (rand() % 6) + 1;
// 	int	*result = malloc(sizeof(int));
// 	*result = value;
// 	printf("Value : %d\n", value);
// 	printf("Thread result : %p\n", result);
// 	return (void *) result;
// }

// int	main()
// {
// 	int	*res;
// 	srand(time(NULL));
// 	pthread_t	th;
// 	if (pthread_create(&th, NULL, &roll_dice, NULL))
// 		return (1);
// 	if (pthread_join(th, (void **) &res))
// 		return (2);
// 	printf("Result : %d\n", *res);
// 	printf("Main Result : %p\n", res);
// 	free(res);
// 	return (0);
// }

//		========== How to create threads in a loop ? ==========
// int mails = 0;
// pthread_mutex_t	mutex;

// void	*routine()
// {
// 	for (int i = 0; i < 10000000; i++)
// 	{
// 		pthread_mutex_lock(&mutex);
// 		mails++;
// 		pthread_mutex_unlock(&mutex);
// 	}
		
// 	return (NULL);
// }

// int	main()
// {
// 	pthread_t th[4];
// 	int i;
// 	pthread_mutex_init(&mutex, NULL);
// 	for (i = 0; i < 4; i++)
// 	{
// 		if (pthread_create(th + i, NULL, &routine, NULL) != 0)
// 		{
// 			perror("Failed to create thread");
// 			return (1);
// 		}
// 		printf("Thread %d has started\n", i);
// 	}
	
// 	for (i = 0; i < 4; i++)
// 	{
// 		if (pthread_join(th[i], NULL) != 0)
// 			return (2);
// 		printf("Thread %d has finished execution\n", i);
// 	}
// 	pthread_mutex_destroy(&mutex);
// 	printf("Number of mails : %d\n", mails);
// 	return (0);
// }


//		========== What is a mutex in C ? ==========
// int mails = 0;
// pthread_mutex_t	mutex;

// void	*routine()
// {
// 	for (int i = 0; i < 10000000; i++)
// 	{
// 		pthread_mutex_lock(&mutex);
// 		mails++;
// 		pthread_mutex_unlock(&mutex);
// 	}
		
// 	return (NULL);
// }

// int	main()
// {
// 	pthread_t t1, t2;
// 	pthread_mutex_init(&mutex, NULL);
// 	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
// 		return (1);
// 	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
// 		return (2);
	
// 	if (pthread_join(t1, NULL) != 0)
// 		return (3);
// 	if (pthread_join(t2, NULL) != 0)
// 		return (4);
// 	pthread_mutex_destroy(&mutex);
// 	printf("Number of mails : %d\n", mails);
// 	return (0);
// }


//		========== What are race conditions ? ==========

// int mails = 0;

// void	*routine()
// {
// 	for (int i = 0; i < 100000; i++)
// 		mails++;
// 	return (NULL);
// }

// int	main()
// {
// 	pthread_t t1, t2;
// 	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
// 		return (1);
// 	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
// 		return (2);
	
// 	if (pthread_join(t1, NULL) != 0)
// 		return (3);
// 	if (pthread_join(t2, NULL) != 0)
// 		return (4);
// 	printf("Number of mails : %d\n", mails);
// 	return (0);
// }



//		========== Difference between processes and threads
// int x = 2;

// void	*routine()
// {
// 	x++;
// 	sleep(2);
// 	printf("Value of x : %d\n", x);
// 	printf("Process id %d\n", getpid());
// 	return (NULL);
// }

// void	*routine2()
// {
// 	sleep(2);
// 	printf("Value of x : %d\n", x);
// 	printf("Process id %d\n", getpid());
// 	return (NULL);
// }
// int main()
// {
// 	pthread_t	t1, t2;
// 	if (pthread_create(&t1, NULL, &routine, NULL))
// 		return (1);
// 	if (pthread_create(&t2, NULL, &routine2, NULL))
// 		return (2);
// 	if (pthread_join(t1, NULL))
// 		return (3);
// 	if (pthread_join(t2, NULL))
// 		return (4);
// }

// int main()
// {
// 	int x = 2;
// 	int	pid = fork();
// 	if (pid == -1)
// 		return (1);
// 	if (pid == 0)
// 		x++;
// 	sleep(2);
// 	printf("Value of x : %d\n", x);
// 	printf("Process id %d\n", getpid());
// 	if (pid != 0)
// 		wait (NULL);
// 	return (0);
// }


//		========== Short introduction to threads ==========
// void	*routine()
// {
// 	printf("Test from threads\n");
// 	sleep(3);
// 	printf("Ending thread\n");
// 	return (NULL);
// }

// int	main()
// {
// 	pthread_t t1, t2;
// 	if (pthread_create(&t1, NULL, &routine, NULL) != 0)
// 		return (1);
// 	if (pthread_create(&t2, NULL, &routine, NULL) != 0)
// 		return (2);
	
// 	if (pthread_join(t1, NULL) != 0)
// 		return (3);
// 	if (pthread_join(t2, NULL) != 0)
// 		return (4);

// 	return (0);
// }