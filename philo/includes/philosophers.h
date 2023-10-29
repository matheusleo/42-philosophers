/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 23:12:49 by mleonard          #+#    #+#             */
/*   Updated: 2023/10/29 03:35:37 by mleonard         ###   ########.fr       */
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
	pthread_create, pthread_join
*/
# include <sys/time.h> //gettimeofday
# include <unistd.h> //usleep

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

// Messages
# define FORK_S 0
# define FORK_MSG "%ldms %d has taken a fork\n"
# define EAT_S 1
# define EAT_MSG "%ldms %d is eating\n"
# define SLEEP_S 2
# define SLEEP_MSG "%ldms %d is sleeping\n"
# define THINK_S 3
# define THINK_MSG "%ldms %d is thinking\n"
# define DEATH_S 4
# define DEATH_MSG "%ldms %d died\n"

typedef struct s_sim	t_sim;
typedef struct s_philo	t_philo;

typedef struct s_fork
{
	int				id;
	pthread_mutex_t	mutex;
}			t_fork;

typedef struct s_philo
{
	pthread_mutex_t	death;
	int					name;
	pthread_t			thread;
	t_sim				*sim_config;
	unsigned long int	last_meal;
	pthread_mutex_t		last_meal_mutex;
	size_t				meal_count;
}			t_philo;

typedef struct s_sim
{
	int					has_stopped;
	pthread_mutex_t		has_stopped_mutex;
	pthread_t			monitor;
	size_t				nb_philo;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	unsigned int		minimum_meals;
	t_fork				**forks;
	t_philo				**philos;
	unsigned long int	start_time;
	pthread_mutex_t		start_time_mutex;
	pthread_mutex_t		output_mutex;
}			t_sim;

// Args
int					validate_args(int argc, char *argv[]);
t_sim				*parse_args(int argc, char *argv[]);

// Simulation
int					init_sim(t_sim *simulation);
int					end_sim(t_sim *simulation);
int					has_sim_stopped(t_sim *simulation);
int					set_sim_stop(t_sim *simulation);

// Forks
t_sim				*create_forks(t_sim *simulation);
t_sim				*destroy_forks(t_sim *simulation);

// Philos
t_sim				*create_philos(t_sim *simulation);
t_sim				*destroy_philos(t_sim *simulation);
t_sim				*init_philos(t_sim *simulation);
void				*philo(void *data);

// Philos actions
void				*lone_philo(void *data);
void				*philo_routine(t_philo *philo, int fork_1, int fork_2);

// Time
long unsigned int	get_current_time(void);
unsigned long int	get_start_time(t_sim *simulation);

// Philo monitor
void				*monitor(void *data);
t_sim				*init_monitor(t_sim *simulation);
int					has_sim_stopped(t_sim *simulation);

// Logs
void				log_status(t_philo *philo, int status);

// Utility functions
int					ft_isdigit(int c);
int					ft_isnb(char *str);
int					ft_atoi(char *str);
void				stop_thread(int ms);

#endif
