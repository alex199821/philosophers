/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:18:29 by macbook           #+#    #+#             */
/*   Updated: 2024/12/30 15:48:59 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

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

void	initialize_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		pthread_mutex_init(&data->philos[i].lock, NULL);
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
}

void initialize_data(t_data *data)
{
	data->dead_philo = false;
	data->dinner_start_time = ft_get_time();
	pthread_mutex_init(&data->dead_mutex, NULL);
	pthread_mutex_init(&data->print, NULL);
	data->philos = malloc(sizeof(t_philos) * data->number_of_philos);
	if (!data->philos)
		return ;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philos);
	initialize_mutexes(data);
	initialize_philos(data);
}