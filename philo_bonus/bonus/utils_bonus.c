/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 22:52:43 by acomet            #+#    #+#             */
/*   Updated: 2023/07/08 04:16:43 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	get_time(void)
{
	struct timeval	time_stamp;
	int				time;

	if (gettimeofday(&time_stamp, NULL))
	{
		printf("Error get time\n");
		return (-1);
	}
	time = ((int)time_stamp.tv_sec * 1000) + ((int)time_stamp.tv_usec / 1000);
	return (time);
}

int	sem_unlock_forks(t_philo *philo)
{
	sem_post(philo->params->fork);
	sem_post(philo->params->fork);
	return (1);
}

int	sem_unlock_print_meal(t_philo *philo)
{
	sem_post(philo->params->print);
	sem_post(philo->meal);
	return (1);
}

void	free_philo(t_params *params, t_philo *philo)
{
	int	i;

	sem_close(params->print);
	sem_close(params->fork);
	i = 0;
	while (i < params->philo_nbr)
	{
		sem_close(philo[i].meal);
		free(philo[i].name);
		i++;
	}
	free(philo);
	free(params);
}
