/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 07:59:30 by macbook           #+#    #+#             */
/*   Updated: 2024/12/20 23:09:41 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

long long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}


void	ft_custom_message(t_data *data, t_philos *philo, char *message)
{
	long long	current_time;

	pthread_mutex_lock(&data->print);
	current_time = ft_get_time() - data->dinner_start_time;
	printf("%lld %d %s", current_time, philo->id, message);
	pthread_mutex_unlock(&data->print);
}

void ft_check_death(t_data *data)
{
	int i;

	while(true)
	{
		i = 0;
		if(ft_get_time() - data->philos[i].time_of_last_meal > data->time_to_die)
		{
			data->dead_philo = true;
			ft_custom_message(data, &data->philos[i], "died\n");
			return;
		}
		i++;
	}
}

void	ft_usleep(long long set_miliseconds)
{
	long long	start;
	long long	elapsed;
	long long	remaining;

	start = ft_get_time();
	while (ft_get_time() - start < set_miliseconds)
	{
		elapsed = ft_get_time() - start;
		remaining = set_miliseconds - elapsed;
		if (remaining > 1000)
			usleep(set_miliseconds / 2);
		else
			while (ft_get_time() - start < set_miliseconds)
				;
	}
}

void	take_forks(t_philos *philo, t_data *data)
{
	if (philo->right_fork > philo->left_fork)
	{
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		ft_custom_message(data, philo, "has taken a fork\n");
		pthread_mutex_lock(&data->forks[philo->right_fork]);
		ft_custom_message(data, philo, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(&data->forks[philo->right_fork]);
		ft_custom_message(data, philo, "has taken a fork\n");
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		ft_custom_message(data, philo, "has taken a fork\n");
	}
}

void	philo_eat(t_philos *philo, t_data *data)
{
	ft_custom_message(data, philo, "is eating\n");
	pthread_mutex_lock(&philo->lock);
	philo->time_of_last_meal = ft_get_time();
	pthread_mutex_unlock(&philo->lock);
	ft_usleep(data->time_to_eat);
	pthread_mutex_lock(&philo->lock);
	philo->amount_of_meals_eaten = philo->amount_of_meals_eaten + 1;
	pthread_mutex_unlock(&philo->lock);
}

void	drop_forks(t_philos *philo, t_data *data)
{
	if (philo->right_fork > philo->left_fork)
	{
		pthread_mutex_unlock(&data->forks[philo->left_fork]);
		pthread_mutex_unlock(&data->forks[philo->right_fork]);
	}
	else
	{
		pthread_mutex_unlock(&data->forks[philo->right_fork]);
		pthread_mutex_unlock(&data->forks[philo->left_fork]);
	}
}

void	philo_think_eat(t_philos *philo, t_data *data)
{
	ft_custom_message(data, philo, "is thinking\n");
	take_forks(philo, data);
	if (data->dead_philo)
	{
		return ;
	}
	philo_eat(philo, data);
	drop_forks(philo, data);
}

void	philo_sleep(t_philos *philo, t_data *data)
{
	// printf("Philosopher %d is sleeping.\n", philo->id);
	ft_custom_message(data, philo, "is sleeping\n");
	// usleep(data->time_to_sleep * 1000);
	ft_usleep(data->time_to_sleep);
}

void	*philosopher_routine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	while (1)
	{
		if (philo->data->dead_philo)
		{
			// ft_custom_message(philo->data, philo, "died\n");
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
	data->philos[0].right_fork = 0;
	data->philos[0].left_fork = data->number_of_philos - 1;
	i = 1;
	while (i < data->number_of_philos)
	{
		data->philos[i].left_fork = i - 1;
		data->philos[i].right_fork = i;
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
		data->philos[i].dead = false;
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
	ft_check_death(data);
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
	data->dead_philo = false;
	data->number_of_philos = 1;
	data->amounto_of_meals = 5;
	data->time_to_die = 410;
	data->time_to_sleep = 200;
	data->time_to_eat = 200;
	data->dinner_start_time = ft_get_time();
	pthread_mutex_init(&data->print, NULL);
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