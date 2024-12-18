/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:31:53 by macbook           #+#    #+#             */
/*   Updated: 2024/12/18 10:33:29 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_philos
{
	int			id;
	long		time_since_last_meal;
}				t_philos;

typedef struct s_data
{
	int			number_of_philos;
	int			amounto_of_meals;
	long		time_to_die;
	long		time_to_eat;
	long		time_to_sleep;
	t_philos	*philos;

}				t_data;