/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 07:59:30 by macbook           #+#    #+#             */
/*   Updated: 2024/12/19 15:58:10 by macbook          ###   ########.fr       */
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

// void mutex_handler(pthread_mutex_t *mutex, t_opcode opcode)
// {
// 	if(LOCK == opcode)
// 		p_thread_mutex_lock(mutex);
// 	if(UNLOCK == opcode)
// }

void	*philosopher_routine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	while (1)
	{
		printf("Philosopher %d is eating.\n", philo->id);
		usleep(1000 * 1000);
		printf("Philosopher %d is sleeping.\n", philo->id);
		usleep(1000 * 1000);
	}
	return (NULL);
}

void	initialize_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		data->philos[i].id = i;
		data->philos[i].amount_of_meals_eaten = 0;
		i++;
	}
	i = 0;
	while (i < data->number_of_philos)
	{
		if (pthread_create(&data->philos[i].philo_thread, NULL,
				(void *)philosopher_routine, &data->philos[i]) != 0)
		{
			perror("Failed to create philosopher thread");
			exit(1);
		}
		i++;
	}
	i = 0;
	while (i < data->number_of_philos)
	{
		pthread_join(data->philos[i].philo_thread, NULL);
		i++;
	}
}

t_data	*initialize_data(void)
{
	t_data	*data;
	int		i;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->number_of_philos = 9;
	data->amounto_of_meals = 5;
	data->time_to_die = 800;
	data->time_to_sleep = 200;
	data->philos = malloc(sizeof(t_philos) * data->number_of_philos);
	if (!data->philos)
		return (NULL);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philos);
	i = 0;
	while (i < data->number_of_philos)
	{
		pthread_mutex_init(&data->philos[i].lock, NULL);
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	initialize_philos(data);
	return (data);
}

int	main(void)
{
	initialize_data();
	return (0);
}

// int	main(void)
// {
// 	pthread_t threads[NUM_THREADS];
// 	int thread_args[NUM_THREADS];
// 	int i = 0;

// 	// Using a while loop to create threads
// 	while (i < NUM_THREADS)
// 	{
// 		thread_args[i] = i; // Assigning an argument to each thread
// 		if (pthread_create(&threads[i], NULL, thread_function,
// 				(void *)&thread_args[i]) != 0)
// 		{
// 			perror("Failed to create thread");
// 			return (1);
// 		}
// 		i++;
// 	}

// 	// Using a while loop to join threads
// 	i = 0;
// 	while (i < NUM_THREADS)
// 	{
// 		if (pthread_join(threads[i], NULL) != 0)
// 		{
// 			perror("Failed to join thread");
// 			return (1);
// 		}
// 		i++;
// 	}

// 	printf("All threads have finished execution.\n");

// 	return (0);
// }