/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:31:53 by macbook           #+#    #+#             */
/*   Updated: 2024/12/20 14:27:55 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdbool.h>
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

struct s_data;

typedef struct s_philos
{
	struct s_data	*data;
	int				id;
	int				amount_of_meals_eaten;
	long long		time_of_last_meal;
	// pthread_mutex_t	*right_fork;
	// pthread_mutex_t	*left_fork;
	bool			dead;
	int				right_fork;
	int				left_fork;
	pthread_t		philo_thread;
	pthread_mutex_t	lock;
}					t_philos;

typedef struct s_data
{
	int				number_of_philos;
	int				amounto_of_meals;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	long long		dinner_start_time;
	pthread_mutex_t	print;
	pthread_mutex_t	*forks;
	t_philos		*philos;

}					t_data;