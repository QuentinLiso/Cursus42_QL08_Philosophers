#include <stdio.h>		// printf
#include <sys/time.h>	// timeval
#include <unistd.h>		// usleep

#define	SEC_TO_MICRO 1000000

void	example()
{
	struct timeval	start_time;
	struct timeval	end_time;
	long			requested_sleep_time;
	long			actual_sleep_time;

	requested_sleep_time = 200 * 1000;
	if (gettimeofday(&start_time, NULL))
		return ;
	usleep(requested_sleep_time);
	if (gettimeofday(&end_time, NULL))
		return ;
	actual_sleep_time = (end_time.tv_sec - start_time.tv_sec) * SEC_TO_MICRO
							+ (end_time.tv_usec - start_time.tv_usec);
	printf("Requested Sleep time : %ld microseconds\n", requested_sleep_time);
	printf("Actual Sleep Time : %ld microseconds\n", actual_sleep_time);
}

int main()
{
	example();
	return (0);
}