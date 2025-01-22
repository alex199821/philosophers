/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:13:43 by macbook           #+#    #+#             */
/*   Updated: 2025/01/22 01:30:01 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	ft_usleep(useconds_t usec)
{
	long long	start;

	start = ft_get_time();
	while ((ft_get_time() - start) < usec)
	{
		usleep(100);
	}
}

bool	ft_sleep_usleep(t_philos *philo, useconds_t usec)
{
	long long	start;

	start = ft_get_time();
	while ((ft_get_time() - start) < usec)
	{
		if (ft_is_dead(philo->data))
		{
			return (false);
		}
		usleep(100);
	}
	return (true);
}
