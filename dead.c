/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:17:51 by macbook           #+#    #+#             */
/*   Updated: 2025/01/03 03:06:48 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

bool	ft_is_dead(t_data *data)
{
	pthread_mutex_lock(&data->dead_mutex);
	if (data->dead_philo)
	{
		pthread_mutex_unlock(&data->dead_mutex);
		return (true);
	}
	pthread_mutex_unlock(&data->dead_mutex);
	return (false);
}

void	ft_set_dead(t_data *data)
{
	pthread_mutex_lock(&data->dead_mutex);
	data->dead_philo = true;
	pthread_mutex_unlock(&data->dead_mutex);
}

long	count_time_of_last_meal(t_data *data, int i)
{
	long	time_of_last_meal;

	pthread_mutex_lock(&data->count_time_mutex);
	time_of_last_meal = data->philos[i].time_of_last_meal;
	pthread_mutex_unlock(&data->count_time_mutex);
	return (time_of_last_meal);
}

void	ft_check_death(t_data *data)
{
	int		i;
	long	time_since_last_meal;
	long	time_of_last_meal;

	while (true)
	{
		i = 0;
		while (i < data->number_of_philos)
		{
			time_of_last_meal = count_time_of_last_meal(data, i);
			time_since_last_meal = ft_get_time() - time_of_last_meal;
			if (time_since_last_meal > data->time_to_die)
			{
				pthread_mutex_lock(&data->philos[i].lock);
				if (data->dead_philo == false)
					ft_set_dead(data);
				ft_death_message(data, i);
				pthread_mutex_unlock(&data->philos[i].lock);
				return ;
			}
			pthread_mutex_unlock(&data->philos[i].lock);
			i++;
		}
		usleep(100);
	}
}
