/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 23:57:36 by acomet            #+#    #+#             */
/*   Updated: 2023/07/08 01:57:49 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleep_philo_eat(t_philo *philo)
{
	if (philo->params->eat_time > philo->params->death_time)
	{
		usleep(philo->params->death_time * 1000);
		while (1)
		{
			pthread_mutex_lock(&philo->params->check_philo);
			if (philo->params->philo_death == 1)
			{
				pthread_mutex_unlock(&philo->params->check_philo);
				mutex_unlock_forks(philo);
				return (1);
			}
			pthread_mutex_unlock(&philo->params->check_philo);
			usleep(100);
		}
	}
	else
		usleep(philo->params->eat_time * 1000);
	return (0);
}

int	sleep_philo_sleep(t_philo *philo)
{
	if (philo->params->eat_time + philo->params->sleep_time
		> philo->params->death_time)
	{
		usleep((philo->params->death_time - philo->params->eat_time) * 1000);
		while (1)
		{
			pthread_mutex_lock(&philo->params->check_philo);
			if (philo->params->philo_death == 1)
			{
				pthread_mutex_unlock(&philo->params->check_philo);
				return (1);
			}
			pthread_mutex_unlock(&philo->params->check_philo);
			usleep(100);
		}
	}
	else
		usleep(philo->params->sleep_time * 1000);
	return (0);
}
