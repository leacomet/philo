/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:31:48 by acomet            #+#    #+#             */
/*   Updated: 2023/07/08 04:21:31 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	only_one_philo(t_params *params)
{
	int	time;
	int	begin;

	begin = get_time();
	if (begin == -1)
		return (1);
	printf("%s0 %d has taken a fork\n\e[0m", BLUE, 1);
	usleep(params->death_time * 1000);
	time = get_time();
	if (time == -1)
		return (-1);
	printf("%s%d %d died\n\e[0m", RED, time - begin, 1);
	return (0);
}

static int	launch_thread(t_params *params, t_philo *philo, int i, int *pid)
{
	int	j;

	philo[i].last_meal = params->begin;
	if (pthread_create(&philo[i].id, NULL, &philo_thread, &philo[i]))
		return (-1);
	j = checker_philo(philo, pid, i);
	if (pthread_join(philo[i].id, NULL))
		return (-1);
	return (j);
}

static int	philo_algo(t_params *params, t_philo *philo, int *pid)
{
	int	i;

	if (params->philo_nbr == 1)
		return (only_one_philo(params));
	i = 0;
	while (i < params->philo_nbr)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			return (-1);
		if (pid[i] == 0)
			return (launch_thread(params, philo, i, pid));
		i++;
	}
	i = 0;
	while (pid && i < params->philo_nbr)
	{
		if (pid[i] != -1)
			waitpid(pid[i], NULL, 0);
		i++;
	}
	return (0);
}

static int	*initialize_pid(t_params *params)
{
	int	i;
	int	*pid;

	pid = malloc(sizeof(int *) * params->philo_nbr);
	if (!pid)
		return (NULL);
	i = 0;
	while (i < params->philo_nbr)
	{
		pid[i] = -1;
		i++;
	}
	return (pid);
}

int	main(int argc, char **argv)
{
	t_params		*params;
	t_philo			*philo;
	int				*pid;

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
	pid = initialize_pid(params);
	if (!pid)
		return (3);
	if (philo_algo(params, philo, pid))
		return (4);
	free_philo(params, philo);
	if (pid)
		free(pid);
	return (0);
}
