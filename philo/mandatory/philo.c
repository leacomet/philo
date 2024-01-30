/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:31:48 by acomet            #+#    #+#             */
/*   Updated: 2023/07/07 23:57:47 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	only_one_philo(t_philo *philo)
{
	int	time;

	philo->params->begin = get_time();
	if (philo->params->begin == -1)
		return (1);
	printf("%s0 %d has taken a fork\n\e[0m", BLUE, philo->data);
	usleep(philo->params->death_time * 1000);
	time = get_time();
	if (time == -1)
		return (-1);
	printf("%s%d %d died\n\e[0m", RED, time - philo->params->begin, philo->data);
	return (0);
}

static int	philo_algo(t_params *params, t_philo *philo)
{
	int	i;

	i = 0;
	if (params->philo_nbr == 1)
		return (only_one_philo(philo));
	params->begin = get_time();
	if (params->begin == -1)
		return (1);
	while (i < params->philo_nbr)
	{
		philo[i].last_meal = params->begin;
		if (pthread_create(&philo[i].id, NULL, &philo_thread, &philo[i]))
			return (1);
		i++;
	}
	if (checker_philo(philo, params))
		return (1);
	i = 0;
	while (i < params->philo_nbr)
	{
		if (pthread_join(philo[i].id, NULL))
			return (1);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_params		*params;
	t_philo			*philo;

	if (argc < 5 || argc > 6)
	{
		printf("Not the right number of arguments\n");
		return (1);
	}
	params = fill_params(argc, argv);
	if (!params)
	{
		printf("Wrong arguments\n");
		return (1);
	}
	philo = fill_philo(params);
	if (!philo)
		return (2);
	if (philo_algo(params, philo))
		return (3);
	free_philo(params, philo);
	return (0);
}
