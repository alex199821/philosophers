/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:13:43 by macbook           #+#    #+#             */
/*   Updated: 2024/12/22 16:13:53 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

// void	ft_usleep(long long set_miliseconds)
// {
// 	long long	start;
// 	long long	elapsed;
// 	long long	remaining;

// 	start = ft_get_time();
// 	while (ft_get_time() - start < set_miliseconds)
// 	{
// 		elapsed = ft_get_time() - start;
// 		remaining = set_miliseconds - elapsed;
// 		if (remaining > 1000)
// 			usleep(set_miliseconds / 2);
// 		else
// 			while (ft_get_time() - start < set_miliseconds)
// 				;
// 	}
// }

void	ft_usleep(useconds_t usec)
{
	long long	start;

	start = ft_get_time();
	while ((ft_get_time() - start) < usec)
	{
		usleep(100);
	}
}