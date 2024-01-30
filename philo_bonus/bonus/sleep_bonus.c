/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sleep_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 02:24:39 by acomet            #+#    #+#             */
/*   Updated: 2023/07/08 02:31:53 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	sleep_philo_eat(t_philo *philo)
{
	if (philo->params->eat_time > philo->params->death_time)
	{
		usleep(philo->params->death_time * 1000);
		while (1)
		{
			sem_wait(philo->meal);
			if (philo->philo_death == 1)
			{
				sem_post(philo->meal);
				sem_unlock_forks(philo);
				return (1);
			}
			sem_post(philo->meal);
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
			sem_wait(philo->meal);
			if (philo->philo_death == 1)
			{
				sem_post(philo->meal);
				return (1);
			}
			sem_post(philo->meal);
			usleep(100);
		}
	}
	else
		usleep(philo->params->sleep_time * 1000);
	return (0);
}
