/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:31:53 by macbook           #+#    #+#             */
/*   Updated: 2024/12/19 11:26:34 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH
}					t_opcode;

typedef struct s_philos
{
	int				id;
	int				amount_of_meals_eaten;
	long			time_since_last_meal;
	pthread_t		philo_thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
}					t_philos;

typedef struct s_data
{
	int				number_of_philos;
	int				amounto_of_meals;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	t_philos		*philos;

}					t_data;