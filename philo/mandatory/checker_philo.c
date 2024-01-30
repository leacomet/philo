/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 21:47:11 by acomet            #+#    #+#             */
/*   Updated: 2023/07/08 01:40:27 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_if_philo_died(t_philo *philo, t_params *params, int i)
{
	int	time;

	if (philo[i].last_meal != -1)
	{
		time = get_time();
		if (time == -1)
			return (1);
		if (time - philo[i].last_meal >= params->death_time)
		{
			params->philo_death = 1;
			pthread_mutex_unlock(&params->check_philo);
			usleep(500);
			pthread_mutex_lock(&params->print);
			printf("%s%d %d died\n\e[0m", RED, time - philo->params->begin,
				i + 1);
			pthread_mutex_unlock(&params->print);
			return (1);
		}
	}
	return (0);
}

int	checker_philo(t_philo *philo, t_params *params)
{
	int	i;

	while (1)
	{
		usleep(100);
		i = 0;
		while (i < params->philo_nbr)
		{
			pthread_mutex_lock(&params->check_philo);
			if (check_if_philo_died(philo, params, i))
				return (0);
			pthread_mutex_unlock(&params->check_philo);
			i++;
		}
		pthread_mutex_lock(&params->philo_end);
		if (params->philo_finish == params->philo_nbr)
		{
			pthread_mutex_unlock(&params->philo_end);
			return (0);
		}
		pthread_mutex_unlock(&params->philo_end);
	}
	return (0);
}
