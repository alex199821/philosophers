/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auplisas <auplisas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 01:36:18 by macbook           #+#    #+#             */
/*   Updated: 2025/01/19 22:41:20 by auplisas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

bool	is_digit(char c)
{
	if(c >= '0' && c <= '9')
		return (true);
	return (false);
}

bool	is_space(char c)
{
	if((c >= 9 && c <= 13) || c == 32)
		return (true);
	return (false);
}

const char	*valid_input(const char *str)
{
	int			len;
	const char	*number;

	len = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		return (print_error_exit("Only Positive Inputs allowed"), NULL);
	if (!is_digit(*str))
		return (print_error_exit("The input is not a correct digit"), NULL);
	number = str;
	while (is_digit(*str++))
		++len;
	if (len > 10)
		return (print_error_exit("The value is bigger then INT_MAX"), NULL);
	return (number);
}

static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	if(!str)
		return (-1);
	while (is_digit(*str))
		num = (num * 10 + (*str++ - 48));
	if (num > INT_MAX)
		return (print_error_exit("The value is bigger then INT_MAX"), -1);
	return (num);
}

bool	parse_input(t_data *data, char **argv)
{
	data->number_of_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	if (data->time_to_die < 60 || data->time_to_eat < 60
		|| data->time_to_sleep < 60)
		return (print_error_exit("Timestamps smaller than 60ms not allowed"),
			false);
	if(data->number_of_philos < 1)
		return (false);
	if(ft_atol(argv[5]) < 0)
		return (false);
	if (argv[5])
		data->amounto_of_meals = ft_atol(argv[5]);
	else
		data->amounto_of_meals = -1;
	return (true);
}
