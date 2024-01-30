/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:32:34 by acomet            #+#    #+#             */
/*   Updated: 2023/07/08 04:27:03 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdio.h>
# include <semaphore.h>
# include <signal.h>

# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIE 4

# define FROSTY_AQUA "\e[38;2;185;234;218m"
# define BLUE "\e[38;2;57;147;221m"
# define GREEN "\e[38;2;12;131;70m"
# define ORANGE "\e[38;2;236;154;41m"
# define RED "\e[38;2;184;12;9m"

typedef struct params
{
	int		philo_nbr;
	int		death_time;
	int		eat_time;
	int		sleep_time;
	int		meal_nbr;
	int		begin;
	sem_t	*print;
	sem_t	*fork;
}	t_params;

typedef struct s_philo
{
	t_params		*params;
	pthread_t		id;
	int				data;
	int				last_meal;
	int				philo_death;
	char			*name;
	sem_t			*meal;
}	t_philo;

/*	initialize	*/
t_params	*fill_params(int argc, char **argv);
t_philo		*fill_philo(t_params *params);

/*	routines	*/
void		*philo_thread(void *param);
int			checker_philo(t_philo *philo, int *pid, int i);

/*	sleep	*/
int			sleep_philo_eat(t_philo *philo);
int			sleep_philo_sleep(t_philo *philo);

/*	utils	*/
int			get_time(void);
int			sem_unlock_forks(t_philo *philo);
int			sem_unlock_print_meal(t_philo *philo);
void		free_philo(t_params *params, t_philo *philo);

#endif
