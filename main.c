/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 07:59:30 by macbook           #+#    #+#             */
/*   Updated: 2024/12/22 23:27:44 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	take_forks(t_philos *philo, t_data *data)
{
	if (philo->left_fork > philo->right_fork)
	{
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		ft_custom_message(data, philo, "has taken a fork\n");
		pthread_mutex_lock(&data->forks[philo->right_fork]);
		ft_custom_message(data, philo, "has taken a fork\n");
	}
	else if (philo->left_fork < philo->right_fork)
	{
		pthread_mutex_lock(&data->forks[philo->right_fork]);
		ft_custom_message(data, philo, "has taken a fork\n");
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		ft_custom_message(data, philo, "has taken a fork\n");
	}
	else
	{
		pthread_mutex_lock(&data->forks[philo->left_fork]);
		ft_custom_message(data, philo, "has taken a fork\n");
		while (!ft_is_dead(data))
		{
			ft_usleep(100);
		}
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
	// if (philo->right_fork > philo->left_fork)
	// {
	// 	pthread_mutex_unlock(&data->forks[philo->left_fork]);
	// 	pthread_mutex_unlock(&data->forks[philo->right_fork]);
	// }
	// else
	// {
	// 	pthread_mutex_unlock(&data->forks[philo->right_fork]);
	// 	pthread_mutex_unlock(&data->forks[philo->left_fork]);
	// }
	if (philo->left_fork < philo->right_fork)
	{
		pthread_mutex_unlock(&data->forks[philo->left_fork]);
		pthread_mutex_unlock(&data->forks[philo->right_fork]);
	}
	else if (philo->left_fork > philo->right_fork)
	{
		pthread_mutex_unlock(&data->forks[philo->right_fork]);
		pthread_mutex_unlock(&data->forks[philo->left_fork]);
	}
	else
	{
		pthread_mutex_unlock(&data->forks[philo->left_fork]);
	}
}

bool	philo_think_eat(t_philos *philo, t_data *data)
{
	ft_custom_message(data, philo, "is thinking\n");
	take_forks(philo, data);
	pthread_mutex_lock(&philo->lock);
	if (ft_is_dead(data))
	{
		pthread_mutex_unlock(&philo->lock);
		drop_forks(philo, data);
		return (false);
	}
	pthread_mutex_unlock(&philo->lock);
	philo_eat(philo, data);
	drop_forks(philo, data);
	return (true);
}

void	philo_sleep(t_philos *philo, t_data *data)
{
	ft_custom_message(data, philo, "is sleeping\n");
	ft_usleep(data->time_to_sleep);
}

void	*philosopher_routine(void *arg)
{
	t_philos	*philo;

	philo = (t_philos *)arg;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2);
	while (!ft_is_dead(philo->data))
	{
		if (!philo_think_eat(philo, philo->data))
		{
			// ft_custom_message(philo->data, philo, "died\n");
			return (NULL);
		}
		// philo_think_eat(philo, philo->data);
		philo_sleep(philo, philo->data);
		usleep(100);
	}
	return (NULL);
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