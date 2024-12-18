/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 07:59:30 by macbook           #+#    #+#             */
/*   Updated: 2024/12/18 10:19:23 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

// int		balance = 0;

// void	write_balance(int new_balance)
// {
// 	usleep(250000);
// 	balance = new_balance;
// }

// int	read_balance(void)
// {
// 	usleep(250000);
// 	return (balance);
// }

// void	*deposit(void *amount)
// {
// 	int	account_balance;

// 	pthread_mutex_lock(&mutex);
// 	account_balance = read_balance();
// 	account_balance += *((int *)amount);
// 	write_balance(account_balance);
// 	pthread_mutex_unlock(&mutex);
// 	return (NULL);
// }

// int	main(void)
// {
// 	pthread_mutex_t mutex;

// 	int before = read_balance();
// 	printf("Before: %d\n", before);

// 	pthread_t thread1;
// 	pthread_t thread2;

// 	pthread_mutex_init(&mutex, NULL);

// 	int deposit1 = 300;
// 	int deposit2 = 200;

// 	pthread_create(&thread1, NULL, deposit, (void *)&deposit1);
// 	pthread_create(&thread2, NULL, deposit, (void *)&deposit2);

// 	pthread_join(thread1, NULL);
// 	pthread_join(thread2, NULL);

// 	pthread_mutex_destroy(&mutex);

// 	int after = read_balance();
// 	printf("After: %d\n", after);

// 	return (0);
// }

// long	time_difference_in_ms(struct timeval *start, struct timeval *end)
// {
// 	long	seconds;
// 	long	microseconds;

// 	seconds = end->tv_sec - start->tv_sec;
// 	microseconds = end->tv_usec - start->tv_usec;
// 	return (seconds * 1000) + (microseconds / 1000);
// }

// int main() {
//     struct timeval tv;
//     gettimeofday(&tv, NULL);

//     printf("Seconds: %ld\n", tv.tv_sec);  // seconds since epoch
//     printf("Microseconds: %ld\n", tv.tv_usec);  // microseconds part
//     return (0);
// }

#define NUM_THREADS 5

t_data	*initialize_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->number_of_philos=8;
	data->amounto_of_meals=5;
	data->time_to_die=800;
	data->time_to_think=200;
	data->time_to_sleep=200;


}
void	*thread_function(void *arg)
{
	int	thread_num;

	thread_num = *((int *)arg);
	printf("Thread %d is running\n", thread_num);
	return (NULL);
}

int	main(void)
{
	pthread_t threads[NUM_THREADS];
	int thread_args[NUM_THREADS];
	int i = 0;

	// Using a while loop to create threads
	while (i < NUM_THREADS)
	{
		thread_args[i] = i; // Assigning an argument to each thread
		if (pthread_create(&threads[i], NULL, thread_function,
				(void *)&thread_args[i]) != 0)
		{
			perror("Failed to create thread");
			return (1);
		}
		i++;
	}

	// Using a while loop to join threads
	i = 0;
	while (i < NUM_THREADS)
	{
		if (pthread_join(threads[i], NULL) != 0)
		{
			perror("Failed to join thread");
			return (1);
		}
		i++;
	}

	printf("All threads have finished execution.\n");

	return (0);
}