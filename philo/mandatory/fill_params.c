/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 19:45:05 by acomet            #+#    #+#             */
/*   Updated: 2023/07/06 15:34:59 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	get_nbr_or_return_neg(char *str)
{
	int	i;
	int	nbr;

	i = 0;
	nbr = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		nbr *= 10;
		nbr += str[i] - 48;
		i++;
	}
	return (nbr);
}

static int	wrong_arguments_values(t_params *params, int argc, char **argv)
{
	params->philo_nbr = get_nbr_or_return_neg(argv[1]);
	params->death_time = get_nbr_or_return_neg(argv[2]);
	params->eat_time = get_nbr_or_return_neg(argv[3]);
	params->sleep_time = get_nbr_or_return_neg(argv[4]);
	if (argc > 5)
		params->meal_nbr = get_nbr_or_return_neg(argv[5]);
	else
		params->meal_nbr = 0;
	if (params->philo_nbr < 1 || params->death_time < 1 || params->eat_time < 1
		|| params->sleep_time < 1 || (argc == 6 && params->meal_nbr < 1))
	{
		free(params);
		return (1);
	}
	return (0);
}

t_params	*fill_params(int argc, char **argv)
{
	t_params		*params;
	struct timeval	time_stamp;

	params = malloc(sizeof(t_params));
	if (!params || wrong_arguments_values(params, argc, argv))
		return (NULL);
	if (gettimeofday(&time_stamp, NULL))
		return (NULL);
	params->begin = (time_stamp.tv_sec * 1000) + (time_stamp.tv_usec / 1000);
	pthread_mutex_init(&params->print, NULL);
	pthread_mutex_init(&params->check_philo, NULL);
	pthread_mutex_init(&params->philo_end, NULL);
	params->philo_death = 0;
	params->philo_finish = 0;
	return (params);
}
