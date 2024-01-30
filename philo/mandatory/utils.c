/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 22:52:43 by acomet            #+#    #+#             */
/*   Updated: 2023/07/06 15:34:33 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	mutex_unlock_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(philo->next_fork);
	return (-1);
}

int	mutex_unlock_print_check_philo(t_philo *philo)
{
	pthread_mutex_unlock(&philo->params->print);
	pthread_mutex_unlock(&philo->params->check_philo);
	return (1);
}

void	free_philo(t_params *params, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < params->philo_nbr)
	{
		pthread_mutex_destroy(&philo[i].fork);
		i++;
	}
	pthread_mutex_destroy(&params->print);
	pthread_mutex_destroy(&params->check_philo);
	pthread_mutex_destroy(&params->philo_end);
	free(philo);
	free(params);
}
