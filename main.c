/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 07:59:30 by macbook           #+#    #+#             */
/*   Updated: 2024/12/20 10:25:10 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

long long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	philo_think_eat(t_philos *philo, t_data *data)
{
	printf("Philosopher %d is thinking.\n", philo->id);
	pthread_mutex_lock(&data->forks[philo->right_fork]);
	printf("Philosopher %d has taken a right fork.\n", philo->id);
	pthread_mutex_lock(&data->forks[philo->left_fork]);
	printf("Philosopher %d has taken a left fork.\n", philo->id);
	if (ft_get_time() - philo->time_of_last_meal > philo->data->time_to_die)
	{
		printf("Philosopher Died\n");
		return ;
	}
	printf("Philosopher %d is eating.\n", philo->id);
	philo->time_of_last_meal = ft_get_time();
	philo->amount_of_meals_eaten = philo->amount_of_meals_eaten + 1;
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(&data->forks[philo->right_fork]);
	pthread_mutex_unlock(&data->forks[philo->left_fork]);
}

void	philo_sleep(t_philos *philo, t_data *data)
{
	printf("Philosopher %d is sleeping.\n", philo->id);
	usleep(data->time_to_sleep * 1000);
}

void	*philosopher_routine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	while (1)
	{
		if (ft_get_time() - philo->time_of_last_meal > philo->data->time_to_die)
		{
			printf("Philosopher Died\n");
			break ;
		}
		philo_think_eat(philo, philo->data);
		philo_sleep(philo, philo->data);
	}
	return (NULL);
}

int	initialize_forks(t_data *data)
{
	int	i;

	i = 0;
	// data->philos[0].left_fork = &data->forks[0];
	// data->philos[0].right_fork = &data->forks[data->number_of_philos - 1];
	// i = 1;
	// while (i < data->number_of_philos)
	// {
	// 	data->philos[i].left_fork = &data->forks[i];
	// 	data->philos[i].right_fork = &data->forks[i - 1];
	// 	i++;
	// }
	data->philos[0].left_fork = 0;
	data->philos[0].right_fork = data->number_of_philos - 1;
	i = 1;
	while (i < data->number_of_philos)
	{
		data->philos[i].left_fork = i;
		// printf("TESTT: %d\n", data->philos[i].left_fork);
		data->philos[i].right_fork = i - 1;
		i++;
	}
	return (0);
}

void	initialize_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		data->philos[i].id = i;
		data->philos[i].data = data;
		data->philos[i].amount_of_meals_eaten = 0;
		data->philos[i].time_of_last_meal = ft_get_time();
		i++;
	}
	i = 0;
	initialize_forks(data);
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
	data->number_of_philos = 12;
	data->amounto_of_meals = 5;
	data->time_to_die = 300;
	data->time_to_sleep = 200;
	data->time_to_eat = 200;
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
	long long	time1;
	long long	time2;

	initialize_data();
	// time1 = ft_get_time();
	// printf("Standart time: %lld\n", time1);
	// usleep(300000);
	// time2 = ft_get_time();
	// printf("Difference in time: %lld\n", time1 - time2);
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