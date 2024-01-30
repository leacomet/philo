/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:07:09 by acomet            #+#    #+#             */
/*   Updated: 2023/07/05 19:44:32 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*fill_philo(t_params *params)
{
	t_philo			*philo;
	int				i;

	philo = malloc(sizeof(t_philo) * params->philo_nbr);
	if (!philo)
		return (NULL);
	i = 0;
	while (i < params->philo_nbr)
	{
		philo[i].data = i + 1;
		philo[i].last_meal = params->begin;
		philo[i].params = params;
		pthread_mutex_init(&philo[i].fork, NULL);
		i++;
	}
	philo[0].next_fork = &philo[i - 1].fork;
	i = 1;
	while (i < params->philo_nbr)
	{
		philo[i].next_fork = &philo[i - 1].fork;
		i++;
	}
	return (philo);
}
