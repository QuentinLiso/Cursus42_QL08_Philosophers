#include <stdio.h>		// printf
#include <sys/time.h>	// timeval
#include <stdint.h>		// uint64_t
#include <unistd.h>		// usleep

//		========== Time prototypes ==========

// === timeval ===
// Linux man page : https://man7.org/linux/man-pages/man3/timeval.3type.html
// Describes times in seconds and microseconds.

// #include <sys/time.h>
// struct timeval {
// 	time_t		tv_sec;		/* Time in seconds, integer */
// 	suseconds_t	tv_usec;	/* Time in microseconds, signed integer */
// };

// === gettimeofday ===
// int gettimeofday(struct timeval *tv, struct timezone *tz);
// Returns 0 for success, -1 for error

#define SEC 3600
#define HOURS 24
#define DAYS 365

void	example_1()
{
	struct timeval	tv;
	if (gettimeofday(&tv, NULL))
		return ;
	printf("%ld seconds\n", tv.tv_sec);
	printf("%ld microseconds\n", tv.tv_usec);
	printf("%ld years passed since 1970\n", tv.tv_sec / (SEC * HOURS * DAYS));
}

uint64_t	get_time(void)
{
	struct timeval	tv;
	uint64_t		seconds;
	uint64_t		microseconds;

	if (gettimeofday(&tv, NULL))
		return (0);
	seconds = tv.tv_sec * (uint64_t)1000;
	microseconds = tv.tv_usec / 1000;
	return (seconds + microseconds);
}

void	example_2()
{
	uint64_t	start_time;
	uint64_t	now;

	start_time = get_time();
	usleep(10000);
	now = get_time();
	printf("Milliseconds elapsed since start of the process : %ld\n", now - start_time);
}

int main()
{
	printf("===== Example 1 =====\n");
	example_1();
	printf("\n===== Example 2 =====\n");
	example_2();
	return (0);
}
