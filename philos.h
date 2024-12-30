/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 08:31:53 by macbook           #+#    #+#             */
/*   Updated: 2024/12/30 17:02:19 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
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
	bool			dead_philo;
	pthread_t		monitor_thread;
	pthread_mutex_t	print;
	pthread_mutex_t	dead_mutex;
	pthread_mutex_t	*forks;
	t_philos		*philos;

}					t_data;

// dead.c
bool				ft_is_dead(t_data *data);
void				ft_death_message(t_data *data, t_philos *philo);
// bool				ft_check_death(void *args);
bool	ft_check_death(t_data *data);
// initialize.c
void				initialize_data(t_data *data);
// message.c
void				ft_custom_message(t_data *data, t_philos *philo,
						char *message);
// time.c
long long			ft_get_time(void);
// usleep.c
void				ft_usleep(useconds_t usec);
// void	ft_usleep(long long set_miliseconds);
// main.c
int					main(int argc, char *argv[]);
void				*philosopher_routine(void *arg);

// utils.c
void				print_error_exit(char *error_message);

// parsing.c
void				parse_input(t_data *data, char **argv);