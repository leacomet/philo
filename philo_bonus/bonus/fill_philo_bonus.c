/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_philo_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 19:07:09 by acomet            #+#    #+#             */
/*   Updated: 2023/07/08 04:25:44 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	get_len(int nbr)
{
	int	len;

	len = 0;
	while (nbr > 0)
	{
		nbr /= 10;
		len++;
	}
	return (len);
}

static char	*get_name(int nbr)
{
	int		len;
	char	*str;

	len = get_len(nbr);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	len--;
	while (len >= 0)
	{
		str[len] = (nbr % 10) + 48;
		nbr /= 10;
		len--;
	}
	return (str);
}

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
		philo[i].philo_death = 0;
		philo[i].params = params;
		philo[i].name = get_name(i + 1);
		if (!philo[i].name)
			return (NULL);
		philo[i].meal = sem_open(philo[i].name, O_CREAT, 0644, 1);
		if (philo[i].meal == SEM_FAILED)
			return (NULL);
		sem_unlink(philo[i].name);
		i++;
	}
	return (philo);
}
