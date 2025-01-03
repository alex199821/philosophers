/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 07:59:30 by macbook           #+#    #+#             */
/*   Updated: 2025/01/03 05:08:47 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	dinner_start(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philos)
	{
		if (pthread_create(&data->philos[i].philo_thread, NULL,
				(void *)philosopher_routine, &data->philos[i]) != 0)
		{
			print_error_exit("Wrong Input");
		}
		i++;
	}
	i = 0;
	ft_philo_life_monitor(data);
	while (i < data->number_of_philos)
	{
		pthread_join(data->philos[i].philo_thread, NULL);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (1);
	if (argc == 5 || argc == 6)
	{
		parse_input(data, argv);
		initialize_data(data);
		dinner_start(data);
	}
	else
	{
		print_error_exit("Wrong Input");
	}
}
