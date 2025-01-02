/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:13:43 by macbook           #+#    #+#             */
/*   Updated: 2025/01/02 18:34:44 by macbook          ###   ########.fr       */
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


// void	ft_usleep(useconds_t usec)
// {
// 	long	start;

// 	start = ft_get_time();
// 	while ((ft_get_time() - start) < usec)
// 		usleep(usec / 2);
// }

// void ft_usleep(useconds_t usec) {
//     long start = ft_get_time(); // Get the starting time in microseconds
//     while ((ft_get_time() - start) < usec) {
//         usleep(10); // Small sleep interval to prevent busy-waiting
//     }
// }