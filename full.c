/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 03:19:37 by macbook           #+#    #+#             */
/*   Updated: 2025/01/03 05:55:49 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	check_full_philo(t_data *data, int i)
{
    // pthread_mutex_lock(&data->philos[i].lock);
	if (data->philos[i].amount_of_meals_eaten == data->amounto_of_meals
		&& data->philos[i].philo_full == false)
	{
		data->philos[i].philo_full = true;
        // pthread_mutex_lock(&data->full_mutex);
		data->amount_of_full_philos = data->amount_of_full_philos + 1;
	    // pthread_mutex_unlock(&data->full_mutex);
    }
	// pthread_mutex_unlock(&data->philos[i].lock);
}

bool	all_philos_full(t_data *data)
{
	pthread_mutex_lock(&data->full_mutex);
	if (data->amount_of_full_philos >= data->number_of_philos)
	{
        pthread_mutex_unlock(&data->full_mutex);
		return (true);
	}
    pthread_mutex_unlock(&data->full_mutex);
	return (false);
}
// bool	ft_death_checker(t_data *data, int i)
// {
// 	long	time_since_last_meal;
// 	long	time_of_last_meal;

// 	time_of_last_meal = count_time_of_last_meal(data, i);
// 	time_since_last_meal = ft_get_time() - time_of_last_meal;
// 	if (time_since_last_meal > data->time_to_die)
// 	{
// 		pthread_mutex_lock(&data->philos[i].lock);
// 		if (data->dead_philo == false)
// 			ft_set_dead(data);
// 		ft_death_message(data, i);
// 		pthread_mutex_unlock(&data->philos[i].lock);
// 		return (false);
// 	}
// 	pthread_mutex_unlock(&data->philos[i].lock);
// 	return (true);
// }
