/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_philo_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 21:47:11 by acomet            #+#    #+#             */
/*   Updated: 2023/07/07 23:35:45 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	philo_dead(t_philo *philo, int *pid, int time, int i)
{
	int	current_pid;

	sem_wait(philo->params->print);
	philo->philo_death = 1;
	current_pid = pid[philo[i].data - 1];
	sem_post(philo[i].meal);
	usleep(500);
	printf("%s%d %d died\n\e[0m", RED, time - philo[i].params->begin,
		philo[i].data);
	kill(0, SIGKILL);
	return (1);
}

int	checker_philo(t_philo *philo, int *pid, int i)
{
	int	time;

	while (1)
	{
		usleep(100);
		sem_wait(philo[i].meal);
		if (philo[i].last_meal == -1)
		{
			sem_post(philo[i].meal);
			return (0);
		}
		time = get_time();
		if (time == -1)
			return (-1);
		if (time - philo[i].last_meal >= philo->params->death_time)
			return (philo_dead(philo, pid, time, i));
		sem_post(philo[i].meal);
	}
	return (0);
}
