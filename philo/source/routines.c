/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 00:42:29 by mleonard          #+#    #+#             */
/*   Updated: 2023/10/29 06:53:25 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static void	philo_sleep(t_sim *simulation, int ms)
{
	time_t	wake_up;

	wake_up = get_current_time() + ms;
	while (get_current_time() < wake_up)
	{
		if (has_sim_stopped(simulation))
			break ;
		usleep(100);
	}
}

void	*lone_philo(void *data)
{
	t_philo	*philo;
	int		id;

	philo = (t_philo *)data;
	id = philo->name;
	while (get_start_time(philo->sim_config) == 0)
		continue ;
	pthread_mutex_lock(&(philo->sim_config->forks[id]->mutex));
	log_status(philo, FORK_S);
	pthread_mutex_unlock(&(philo->sim_config->forks[id]->mutex));
	philo_sleep(philo->sim_config, philo->sim_config->time_to_die);
	log_status(philo, DEATH_S);
	return (NULL);
}

static void	*think(t_philo *philo)
{
	long int	time_to_think;

	log_status(philo, THINK_S);
	time_to_think = 500;
	usleep(time_to_think);
	return (NULL);
}

void	*philo_routine(t_philo *philo, int fork_1, int fork_2)
{
	pthread_mutex_lock(&(philo->sim_config->forks[fork_1]->mutex));
	log_status(philo, FORK_S);
	pthread_mutex_lock(&(philo->sim_config->forks[fork_2]->mutex));
	log_status(philo, FORK_S);
	log_status(philo, EAT_S);
	pthread_mutex_lock(&(philo->last_meal_mutex));
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&(philo->last_meal_mutex));
	philo_sleep(philo->sim_config, philo->sim_config->time_to_eat);
	pthread_mutex_lock(&(philo->last_meal_mutex));
	philo->meal_count++;
	pthread_mutex_unlock(&(philo->last_meal_mutex));
	pthread_mutex_unlock(&(philo->sim_config->forks[fork_1]->mutex));
	pthread_mutex_unlock(&(philo->sim_config->forks[fork_2]->mutex));
	log_status(philo, SLEEP_S);
	philo_sleep(philo->sim_config, philo->sim_config->time_to_sleep);
	think(philo);
	return (NULL);
}

void	*philo(void *data)
{
	t_philo	*philo;
	int		id;
	int		fork_1;
	int		fork_2;

	philo = (t_philo *)data;
	id = philo->name;
	fork_1 = id;
	fork_2 = (id + 1) % philo->sim_config->nb_philo;
	if (id % 2)
	{
		fork_1 = (id + 1) % philo->sim_config->nb_philo;
		fork_2 = id;
	}
	while (!has_sim_stopped(philo->sim_config))
	{
		if (get_start_time(philo->sim_config) == 0)
			continue ;
		philo_routine(philo, fork_1, fork_2);
	}
	return (NULL);
}
