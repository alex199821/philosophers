/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: macbook <macbook@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 01:42:11 by macbook           #+#    #+#             */
/*   Updated: 2024/12/30 01:42:53 by macbook          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philos.h"

void	print_error_exit(char *error_message)
{
	printf("%s\n", error_message);
	exit(EXIT_FAILURE);
}
