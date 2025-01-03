/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:11:54 by macbook           #+#    #+#             */
/*   Updated: 2025/01/03 05:13:15 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	ft_custom_message(t_data *data, t_philos *philo, char *message)
{
	long	current_time;

	pthread_mutex_lock(&data->print);
	if (ft_is_dead(data))
	{
		pthread_mutex_unlock(&data->print);
		return ;
	}
	current_time = ft_get_time() - data->dinner_start_time;
	printf("%ld %d %s", current_time, philo->id, message);
	pthread_mutex_unlock(&data->print);
}

void	ft_death_message(t_data *data, int i)
{
	long	current_time;

	pthread_mutex_lock(&data->print);
	current_time = ft_get_time() - data->dinner_start_time;
	if(!all_philos_full(data))
		printf("%ld %d died\n", current_time, i);
	pthread_mutex_unlock(&data->print);
}
