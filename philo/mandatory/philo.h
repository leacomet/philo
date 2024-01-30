/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acomet <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 17:32:34 by acomet            #+#    #+#             */
/*   Updated: 2023/07/08 01:53:23 by acomet           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>

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
	int				philo_nbr;
	int				death_time;
	int				eat_time;
	int				sleep_time;
	int				meal_nbr;
	int				begin;
	int				philo_death;
	int				philo_finish;
	pthread_mutex_t	print;
	pthread_mutex_t	check_philo;
	pthread_mutex_t	philo_end;
}	t_params;

typedef struct s_philo
{
	t_params		*params;
	pthread_t		id;
	pthread_mutex_t	fork;
	pthread_mutex_t	*next_fork;
	int				data;
	int				last_meal;
}	t_philo;

/*	initialize	*/
t_params	*fill_params(int argc, char **argv);
t_philo		*fill_philo(t_params *params);

/*	routines	*/
void		*philo_thread(void *param);
int			checker_philo(t_philo *philo, t_params *params);

/*	sleep	*/
int			sleep_philo_eat(t_philo *philo);
int			sleep_philo_sleep(t_philo *philo);

/*	utils	*/
int			get_time(void);
int			mutex_unlock_forks(t_philo *philo);
int			mutex_unlock_print_check_philo(t_philo *philo);
void		free_philo(t_params *params, t_philo *philo);

#endif
