#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>


//		========== Working with multiple pipes ==========
// int main()
// {
// 	int	fd[3][2];
// 	int i;
// 	for (i = 0; i < 3; i++)
// 	{
// 		if (pipe(fd[i]) < 0)
// 		{
// 			// Il faudrait close les fd open si on a une erreur au 3eme par exemple
// 			return (1);
// 		}
// 	}
// 	int	pid1 = fork();
// 	if (pid1 < 0)
// 		return (2);
// 	if (pid1 == 0)
// 	{
// 		close(fd[0][1]);
// 		close(fd[1][0]);
// 		close(fd[2][0]);
// 		close(fd[2][1]);
// 		int x;
// 		if (read(fd[0][0], &x, sizeof(int)) < 0)
// 			return (3);
// 		x += 5;
// 		if (write(fd[1][1], &x, sizeof(int)) < 0)
// 			return (4);
// 		close(fd[0][0]);
// 		close(fd[1][1]);
// 		return (0);
// 	}

// 	int	pid2 = fork();
// 	if (pid2 < 0)
// 		return (5);
// 	if (pid2 == 0)
// 	{
// 		close(fd[1][1]);
// 		close(fd[2][0]);
// 		close(fd[0][0]);
// 		close(fd[0][1]);
// 		int x;
// 		if (read(fd[1][0], &x, sizeof(int)) < 0)
// 			return (6);
// 		x += 5;
// 		if (write(fd[2][1], &x, sizeof(int)) < 0)
// 			return (7);
// 		close(fd[1][0]);
// 		close(fd[2][2]);
// 		return (0);
// 	}

// 	close(fd[0][0]);
// 	close(fd[2][1]);
// 	close(fd[1][0]);
// 	close(fd[1][1]);
// 	int	x;
// 	printf("Input number : ");
// 	scanf("%d", &x);
// 	if (write(fd[0][1], &x, sizeof(int)) < 0)
// 		return (8);
// 	if (read(fd[2][0], &x, sizeof(int)) < 0)
// 		return (9);
// 	printf("Result is : %d\n", x);
// 	close(fd[0][1]);
// 	close(fd[2][0]);
// 	waitpid(pid1, NULL, 0);
// 	waitpid(pid2, NULL, 0);
// 	return (0);
// }
	
//		========== Simulating the pipe operator in C ==========
// int main()
// {
// 	int	fd[2];

// 	if (pipe(fd) == -1)
// 		return (1);
// 	int	pid1 = fork();
// 	if (pid1 < 0)
// 		return (2);
// 	if (pid1 == 0)
// 	{
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[0]);
// 		close(fd[1]);
// 		execlp("ping", "ping", "-c", "5", "google.com", NULL);
// 	}
// 	int pid2 = fork();
// 	if (pid2 < 0)
// 		return (3);
// 	if (pid2 == 0)
// 	{
// 		dup2(fd[0], STDIN_FILENO);
// 		close(fd[0]);
// 		close(fd[1]);
// 		execlp("grep", "grep", "rtt", NULL);
// 	}
// 	close(fd[0]);
// 	close(fd[1]);
// 	waitpid(pid1, NULL, 0);
// 	waitpid(pid2, NULL, 0);
// 	return (0);
// }


//		========== How to send a string through a pipe ==========
// int main()
// {
// 	int	fd[2];
// 	if (pipe(fd) == -1)
// 		return (1);
// 	int pid = fork();
// 	if (pid < 0)
// 		return (2);
// 	if (pid == 0)
// 	{
// 		close(fd[0]);
// 		char	str[200];
// 		printf("Input string : ");
// 		fgets(str, 200, stdin);
// 		str[strlen(str) - 1] = '\0';
// 		int	n = strlen(str) + 1;
// 		if (write(fd[1], &n, sizeof(int)) < 0)
// 			return (3);
// 		if (write(fd[1], str, sizeof(char) * n) < 0)
// 			return (4);
// 		close(fd[1]);
// 	}
// 	else
// 	{
// 		close(fd[1]);
// 		char	str[200];
// 		int 	n;
// 		if (read(fd[0], &n, sizeof(int)) < 0)
// 			return (5);
// 		if (read(fd[0], str, sizeof(char) * n) < 0)
// 			return (6);
		
// 		printf("Received : %s\n", str);
// 		close(fd[0]);
// 		wait(NULL);
// 	}

// 	return (0);
// }


//		========== How to send an array through a pipe ==========
// 2 processes 
// 1) Child process should generate random numbers and send them to the parent
// 2) Parent is going to sum all the numbers and print the result

// int main()
// {
// 	int	fd[2];
// 	if (pipe(fd) == -1)
// 		return (1);
// 	int pid = fork();
// 	if (pid == -1)
// 		return (2);
// 	if (pid == 0)
// 	{
// 		// Child process
// 		close(fd[0]);
// 		int	n, i;
// 		int	arr[10];
// 		srand(time(NULL));
// 		n = rand() % 10 + 1;
// 		printf("Generated : ");
// 		for (i = 0; i < n; i++)
// 		{
// 			arr[i] = rand() % 11;
// 			printf("%d ", arr[i]);
// 		}
// 		printf("\n");
// 		if (write(fd[1], &n, sizeof(int)) < 0)
// 			return (3);
// 		printf("Sent n = %d\n", n);
// 		if (write(fd[1], arr, sizeof(int) * n) < 0)
// 			return (4);
// 		printf("Sent array\n");
// 		close(fd[1]);
// 	}
// 	else
// 	{
// 		// Parent process
// 		close(fd[1]);
// 		int arr[10];
// 		int n, i, sum = 0;
// 		if (read(fd[0], &n, sizeof(int)) < 0)
// 			return (5);
// 		printf("Received n = %d\n", n);
// 		if (read(fd[0], arr, sizeof(int) * n) < 0)
// 			return (6);
// 		printf("Received array\n");
// 		close(fd[0]);
// 		for (i = 0; i < n; i++)
// 			sum += arr[i];
// 		printf("Result is : %d\n", sum);
// 		wait(NULL);
// 	}
// }


//		========== Communicating between processes using signals ==========
// void	handle_sigusr1(int sig)
// {
// 	(void) sig;
// 	printf("Hint : result should be 15...\n");
// }

// int main()
// {
// 	int pid = fork();
// 	if (pid == -1)
// 		return (1);
// 	if (pid == 0)
// 	{
// 		sleep(5);
// 		kill(getppid(), SIGUSR1);
// 	}
// 	else
// 	{
// 		struct sigaction sa;
// 		sa.sa_flags = SA_RESTART;
// 		sa.sa_handler = &handle_sigusr1;
// 		sigaction(SIGUSR1, &sa, NULL);

// 		int x;
// 		printf("What is the result of 3 x 5 : ");
// 		scanf("%d", &x);
// 		if (x == 15)
// 			printf("Right!");
// 		else
// 			printf("Wrong!");
// 		wait(NULL);
// 	}
// }


//		========== Handling signals ==========
// void	handle_sigtstp(int sig)
// {
// 	(void)sig;
// 	printf("Stop not allowed\n");
// }

// int main()
// {
// 	struct sigaction sa;
// 	sa.sa_handler = &handle_sigtstp;
// 	sa.sa_flags = SA_RESTART;
// 	sigaction(SIGTSTP, &sa, NULL);

// 	while (1);
// 	return (0);
// }


//		========== Stopping and continuing the execution of a process ==========
// int main()
// {
// 	int	pid = fork();
// 	if (pid == - 1)
// 		return (1);
// 	if (pid == 0)
// 	{
// 		while (1)
// 		{
// 			printf("Some output\n");
// 			usleep(50000);
// 		}
// 	}
// 	else
// 	{
// 		kill(pid, SIGSTOP);
// 		int	t = 1;
// 		while (t > 0)
// 		{
// 			printf("Time in seconds for execution : ");
// 			scanf("%d", &t);
// 			if (t > 0)
// 			{
// 				kill(pid, SIGCONT);
// 				sleep(t);
// 				kill(pid, SIGSTOP);
// 			}
// 		}
// 		kill(pid, SIGKILL);
// 		wait(NULL);
// 	}
// 	return (0);
// }


//		========== Short introduction to signals in C ==========
// int main()
// {
// 	int	pid = fork();
// 	if (pid == -1)
// 	{
// 		return (1);
// 	}

// 	if (pid == 0)
// 	{
// 		while (1)
// 		{
// 			printf("Some text goes here\n");
// 			usleep(50000);
// 		}
// 	}
// 	else
// 	{
// 		sleep(1);
// 		kill(pid, SIGKILL);
// 		wait(NULL);
// 	}

// 	return (0);
// }


//		========== Redirecting standard output in C ==========
// int main()
// {
// 	int	pid = fork();
// 	if (pid == -1)
// 		return (1);
// 	if (pid == 0)
// 	{
// 		int file = open("pingResults.txt", O_WRONLY | O_CREAT, 0777);
// 		if (file == -1)
// 		{
// 			return (2);
// 		}
// 		printf("The fd to pingResults : %d\n", file);
// 		dup2(file, STDOUT_FILENO);
// 		close(file);

// 		int err = execlp("ping", "ping", "-c", "3", "google.com", NULL);
// 		if (err == -1)
// 		{
// 			printf("Could not find program to execute\n");
// 			return (2);
// 		}
// 	}
// 	else
// 	{
// 		int wstatus;
// 		wait(&wstatus);
// 		if(WIFEXITED(wstatus))
// 		{
// 			int statusCode = WEXITSTATUS(wstatus);
// 			if (statusCode == 0)
// 			{
// 				printf("Sucess!\n");
// 			}
// 			else
// 			{
// 				printf("Failure with status code %d!\n", statusCode);
// 			}
// 		}
// 	}
// 	return (0);
// }


// 			========== Getting exit status in C ============
// int main()
// {
// 	int	pid = fork();
// 	if (pid == -1)
// 		return (1);
// 	if (pid == 0)
// 	{
// 		int err = execlp("ping", "ping", "-c", "3", "google.com", NULL);
// 		if (err == -1)
// 		{
// 			printf("Could not find program to execute\n");
// 			return (2);
// 		}
// 	}
// 	else
// 	{
// 		int wstatus;
// 		wait(&wstatus);
// 		if(WIFEXITED(wstatus))
// 		{
// 			int statusCode = WEXITSTATUS(wstatus);
// 			if (statusCode == 0)
// 			{
// 				printf("Sucess!\n");
// 			}
// 			else
// 			{
// 				printf("Failure with status code %d!\n", statusCode);
// 			}
// 		}
// 	}
// 	return (0);
// }


//  			======= Executing commands in C ============
// int main()
// {
// 	int	pid = fork();
// 	if (pid == -1)
// 		return 1;
// 	if (pid == 0)
// 	{
// 		execlp("ping", "ping", "-c", "3", "google.com", NULL);
// 		printf("This line should not be printed\n");
// 	}
// 	else
// 	{
// 		wait(NULL);
// 		printf("Success :)\n");
// 	}
// 	return (0);
// }
