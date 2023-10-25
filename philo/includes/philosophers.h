/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 23:12:49 by mleonard          #+#    #+#             */
/*   Updated: 2023/10/25 10:46:54 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// Libs
# include <stdio.h> //printf
# include <stdlib.h> //exit
# include <pthread.h>
/*
	pthread_mutex_lock, pthread_mutex_unlock
*/

# define TRUE 1
# define FALSE 0
# define INT_MAX 2147483647
# define NB_PHILOS_POS 1
# define TIME_TO_DIE_POS 2
# define TIME_TO_EAT_POS 3
# define TIME_TO_SLEEP_POS 4
# define MIN_MEALS_POS 5
# define MSG_USAGE "Use as:\n \
philo <number_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep> [minimum_meals]\n"
# define ERR_NB_ARGS "Invalid number of arguments\n"
# define ERRNO_NB_ARGS 1
# define ERR_TYPE_ARGS "Invalid type of arguments\n"
# define ERRNO_TYPE_ARGS 2
# define ERR_NB_PHILOS "Maximum number of philos reached. \
Try a value smaller than 250\n"
# define ERRNO_NB_PHILOS 3
# define NO_ERR 0

typedef struct s_fork
{
	int				fork_name;
	pthread_mutex_t	fork_mutex;
}			t_fork;

typedef struct s_sim
{
	unsigned int	nb_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	minimum_meals;
	t_fork			**forks;
}			t_sim;

// Args
int		validate_args(int argc, char *argv[]);
t_sim	*parse_args(t_sim *simulation, int argc, char *argv[]);

// Forks
t_sim	*init_forks(t_sim *simulation);
t_sim	*destroy_forks(t_sim *simulation);

// Utility functions
int		ft_isdigit(int c);
int		ft_isnb(char *str);
int		ft_atoi(char *str);

#endif
