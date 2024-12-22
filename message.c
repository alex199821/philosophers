/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   message.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:11:54 by macbook           #+#    #+#             */
/*   Updated: 2024/12/22 16:12:54 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	ft_custom_message(t_data *data, t_philos *philo, char *message)
{
	long long	current_time;

	pthread_mutex_lock(&data->print);
	if (ft_is_dead(data))
	{
		pthread_mutex_unlock(&data->print);
		return ;
	}
	current_time = ft_get_time() - data->dinner_start_time;
	printf("%lld %d %s", current_time, philo->id, message);
	pthread_mutex_unlock(&data->print);
}
