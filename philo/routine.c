/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 02:28:09 by macbook           #+#    #+#             */
/*   Updated: 2025/01/21 22:32:05 by macbook          ###   ########.fr       */
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

void	drop_forks(t_philos *philo, t_data *data)
{
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

bool	philo_eat(t_philos *philo, t_data *data)
{
	take_forks(philo, data);
	pthread_mutex_lock(&philo->lock);
	if (ft_is_dead(data))
	{
		pthread_mutex_unlock(&philo->lock);
		drop_forks(philo, data);
		return (false);
	}
	pthread_mutex_unlock(&philo->lock);
	pthread_mutex_lock(&philo->data->count_time_mutex);
	philo->time_of_last_meal = ft_get_time();
	pthread_mutex_unlock(&philo->data->count_time_mutex);
	ft_custom_message(data, philo, "is eating\n");
	ft_usleep(data->time_to_eat);
	pthread_mutex_lock(&philo->data->philos[philo->id].lock);
	pthread_mutex_lock(&data->full_mutex);
	philo->amount_of_meals_eaten = philo->amount_of_meals_eaten + 1;
	pthread_mutex_unlock(&data->full_mutex);
	pthread_mutex_unlock(&philo->data->philos[philo->id].lock);
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
	ft_custom_message(philo->data, philo, "is thinking\n");
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2);
	while (!ft_is_dead(philo->data) && !all_philos_full(philo->data))
	{
		if (all_philos_full(philo->data)) 
			return (NULL);
		philo_eat(philo, philo->data);
		if (all_philos_full(philo->data))
			return (NULL);
		philo_sleep(philo, philo->data);
		if (all_philos_full(philo->data))
			return (NULL);
		ft_custom_message(philo->data, philo, "is thinking\n");
		usleep(100);
	}
	return (NULL);
}
