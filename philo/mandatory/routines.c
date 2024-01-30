/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 14:14:26 by acomet            #+#    #+#             */
/*   Updated: 2023/07/08 04:56:00 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	one_philo_is_dead(t_philo *philo, int *time)
{
	pthread_mutex_lock(&philo->params->check_philo);
	if (philo->params->philo_death)
	{
		pthread_mutex_unlock(&philo->params->check_philo);
		return (1);
	}
	pthread_mutex_lock(&philo->params->print);
	*time = get_time();
	if (*time == -1 || *time - philo->last_meal >= philo->params->death_time)
		return (mutex_unlock_print_check_philo(philo));
	return (0);
}

static int	print_philo(t_philo *philo, int id)
{
	int	time;
	int	begin;

	if (one_philo_is_dead(philo, &time))
		return (1);
	begin = time - philo->params->begin;
	if (id == EAT)
	{
		printf("%s%d %d has taken a fork\n\e[0m", BLUE, begin, philo->data);
		printf("%s%d %d has taken a fork\n\e[0m", BLUE, begin, philo->data);
		printf("%s%d %d is eating\n\e[0m", ORANGE, begin, philo->data);
		pthread_mutex_unlock(&philo->params->print);
		philo->last_meal = time;
		pthread_mutex_unlock(&philo->params->check_philo);
		return (0);
	}
	else if (id == SLEEP)
		printf("%s%d %d is sleeping\n\e[0m", FROSTY_AQUA, begin, philo->data);
	else if (id == THINK)
		printf("%s%d %d is thinking\n\e[0m", GREEN, begin, philo->data);
	pthread_mutex_unlock(&philo->params->print);
	pthread_mutex_unlock(&philo->params->check_philo);
	return (0);
}

static int	thread_algo(t_philo *philo)
{
	pthread_mutex_lock(&philo->fork);
	pthread_mutex_lock(philo->next_fork);
	if (print_philo(philo, EAT))
		return (mutex_unlock_forks(philo));
	if (sleep_philo_eat(philo))
		return (1);
	mutex_unlock_forks(philo);
	if (print_philo(philo, SLEEP))
		return (1);
	if (sleep_philo_sleep(philo))
		return (1);
	if (print_philo(philo, THINK))
		return (1);
	if (philo->data == philo->params->philo_nbr && philo->data % 2 == 1)
		usleep(500);
	return (0);
}

static void	*philo_thread_infinite(t_philo *philo)
{
	while (1)
	{
		if (thread_algo(philo))
			return (NULL);
	}
}

void	*philo_thread(void *param)
{
	t_philo	*philo;
	int		i;

	philo = param;
	if (philo->data % 2 == 1)
		usleep(1000);
	if (philo->params->meal_nbr == 0)
		philo_thread_infinite(philo);
	else
	{
		i = philo->params->meal_nbr;
		while (i > 0)
		{
			if (thread_algo(philo))
				return (NULL);
			i--;
		}
	}
	pthread_mutex_lock(&philo->params->philo_end);
	philo->params->philo_finish++;
	pthread_mutex_unlock(&philo->params->philo_end);
	pthread_mutex_lock(&philo->params->check_philo);
	philo->last_meal = -1;
	pthread_mutex_unlock(&philo->params->check_philo);
	return (NULL);
}
