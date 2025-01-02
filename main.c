/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 07:59:30 by macbook           #+#    #+#             */
/*   Updated: 2025/01/02 17:58:48 by macbook          ###   ########.fr       */
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
	pthread_mutex_lock(&philo->data->table_mutex);
	philo->time_of_last_meal = ft_get_time();
	pthread_mutex_unlock(&philo->data->table_mutex);
	ft_custom_message(data, philo, "is eating\n");
	ft_usleep(data->time_to_eat);
	// pthread_mutex_lock(&philo->lock);
	philo->amount_of_meals_eaten = philo->amount_of_meals_eaten + 1;
	// pthread_mutex_unlock(&philo->lock);
	drop_forks(philo, data);
	return (true);
}

void	philo_thinking(t_philos *philo, t_data *data)
{
	ft_custom_message(data, philo, "is thinking\n");
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
	// philo->time_of_last_meal = ft_get_time();
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2);
	while (!ft_is_dead(philo->data))
	{
		// if (!philo_eat(philo, philo->data))
		// {
		// 	// ft_custom_message(philo->data, philo, "died\n");
		// 	return (NULL);
		// }
		philo_eat(philo, philo->data);
		philo_sleep(philo, philo->data);
		philo_thinking(philo, philo->data);
		usleep(100);
	}
	return (NULL);
}

void	dinner_start(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		if (pthread_create(&data->philos[i].philo_thread, NULL,
				(void *)philosopher_routine, &data->philos[i]) != 0)
		{
			print_error_exit("Wrong Input");
		}
		i++;
	}
	i = 0;
	ft_check_death(data);
	// pthread_create(&data->monitor_thread, NULL, (void *)ft_check_death,&data);
	while (i < data->number_of_philos)
	{
		pthread_join(data->philos[i].philo_thread, NULL);
		i++;
	}
	// pthread_join(data->monitor_thread, NULL);
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (argc == 5 || argc == 6)
	{
		parse_input(data, argv);
		initialize_data(data);
		dinner_start(data);
		// clean(&data);
	}
	else
	{
		print_error_exit("Wrong Input");
	}
}
