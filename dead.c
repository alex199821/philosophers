/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:17:51 by macbook           #+#    #+#             */
/*   Updated: 2024/12/30 17:01:50 by macbook          ###   ########.fr       */
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

void	ft_death_message(t_data *data, t_philos *philo)
{
	long long	current_time;

	pthread_mutex_lock(&data->print);
	current_time = ft_get_time() - data->dinner_start_time;
	printf("%lld %d died\n", current_time, philo->id);
	pthread_mutex_unlock(&data->print);
}

// bool	ft_check_death(void *args)
bool	ft_check_death(t_data *data)
{
	int i;
	long long time_since_last_meal;
	long long current_time;
	// t_data *data;

	// data = (t_data *)args;
	while (true)
	{
		i = 0;
		while (i < data->number_of_philos)
		{
			pthread_mutex_lock(&data->philos[i].lock);
			time_since_last_meal = ft_get_time()
				- data->philos[i].time_of_last_meal;
			if (time_since_last_meal > data->time_to_die)
			{
				if (data->dead_philo == false)
				{
					pthread_mutex_lock(&data->dead_mutex);
					data->dead_philo = true;
					pthread_mutex_unlock(&data->dead_mutex);
				}
				// ft_death_message(data, &data->philos[i]);
				// printf("%d died\n", i);
				pthread_mutex_lock(&data->print);
				current_time = ft_get_time() - data->dinner_start_time;
				printf("%lld %d died\n", current_time, i);
				pthread_mutex_unlock(&data->print);
				pthread_mutex_unlock(&data->philos[i].lock);
				return (false);
			}
			pthread_mutex_unlock(&data->philos[i].lock);
			i++;
		}
	}
	return (true);
}