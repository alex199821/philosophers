/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 07:15:00 by macbook           #+#    #+#             */
/*   Updated: 2025/01/03 07:54:06 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	ft_clean(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		pthread_mutex_destroy(&data->forks[i]);
		pthread_mutex_destroy(&data->philos[i].lock);
		i++;
	}
	pthread_mutex_destroy(&data->count_time_mutex);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->dead_mutex);
	pthread_mutex_destroy(&data->full_mutex);
	free(data->philos);
	free(data->forks);
	free(data);
}

