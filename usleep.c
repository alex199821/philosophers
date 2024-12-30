/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usleep.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:13:43 by macbook           #+#    #+#             */
/*   Updated: 2024/12/30 18:10:14 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

// void	ft_usleep(useconds_t usec)
// {
// 	long long	start;

// 	start = ft_get_time();
// 	while ((ft_get_time() - start) < usec)
// 	{
// 		usleep(100);
// 	}
// }

void	ft_usleep(useconds_t usec)
{
	long	start;
	long	elapsed;
	long	rem;

	start = ft_get_time();
	while (ft_get_time() - start < usec)
	{
		// if (simulation_finished(table))
		// 	break ;
		elapsed = ft_get_time() - start;
		rem = usec - elapsed;
		if (rem > 1e3)
			usleep(rem / 2);
		else
		{
			while (ft_get_time() - start < usec)
				;
		}
	}
}
