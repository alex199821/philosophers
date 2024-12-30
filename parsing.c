/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 01:36:18 by macbook           #+#    #+#             */
/*   Updated: 2024/12/30 02:08:57 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
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
		print_error_exit("Feed me only positive values");
	if (!is_digit(*str))
		print_error_exit("The input is not a correct digit");
	number = str;
	while (is_digit(*str++))
		++len;
	if (len > 10)
		print_error_exit("The value is bigger then INT_MAX");
	return (number);
}

static long	ft_atol(const char *str)
{
	long	num;

	num = 0;
	str = valid_input(str);
	while (is_digit(*str))
		num = (num * 10 + (*str++ - 48));
	if (num > INT_MAX)
		print_error_exit("The value is bigger then INT_MAX");
	return (num);
}

void	parse_input(t_data *data, char **argv)
{
	data->number_of_philos = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]) * 1000;
	data->time_to_eat = ft_atol(argv[3]) * 1000;
	data->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (data->time_to_die / 1000 < 60 || data->time_to_eat / 1000 < 60
		|| data->time_to_sleep / 1000 < 60)
		print_error_exit("Timestamps smaller then 60ms are not usesful");
	if (argv[5])
		data->amounto_of_meals = ft_atol(argv[5]);
	else
		data->amounto_of_meals = -1;
}