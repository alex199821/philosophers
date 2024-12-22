/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/22 16:12:48 by macbook           #+#    #+#             */
/*   Updated: 2024/12/22 16:13:04 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

long long	ft_get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
