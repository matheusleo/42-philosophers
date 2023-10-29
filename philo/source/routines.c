/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 00:42:29 by mleonard          #+#    #+#             */
/*   Updated: 2023/10/29 03:38:50 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

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
	stop_thread(philo->sim_config->time_to_die);
	log_status(philo, DEATH_S);
	return (NULL);
}

void	*think(t_philo *philo)
{
	int	time_to_think;

	// pthread_mutex_lock(&(philo->last_meal_mutex));
	// time_to_think = (philo->sim_config->time_to_die
	// 								- (get_current_time() - philo->last_meal)
	// 								- philo->sim_config->time_to_eat
	// 								- philo->sim_config->time_to_sleep) / 2;
	// pthread_mutex_unlock(&(philo->last_meal_mutex));
	log_status(philo, THINK_S);
	// if (time_to_think < 0)
		// time_to_think = 0;
		time_to_think = 500;
	usleep(time_to_think);
	return (NULL);
}

void	*philo_routine(t_philo *philo, int fork_1, int fork_2)
{
	pthread_mutex_lock(&(philo->sim_config->forks[fork_1]->mutex));
	log_status(philo, FORK_S);
	pthread_mutex_lock(&(philo->sim_config->forks[fork_2]->mutex));
	pthread_mutex_lock(&(philo->death));
	log_status(philo, FORK_S);
	log_status(philo, EAT_S);
	pthread_mutex_lock(&(philo->last_meal_mutex));
	philo->last_meal = get_current_time();
	philo->meal_count++;
	pthread_mutex_unlock(&(philo->last_meal_mutex));
	pthread_mutex_unlock(&(philo->death));
	stop_thread(philo->sim_config->time_to_eat);
	pthread_mutex_unlock(&(philo->sim_config->forks[fork_1]->mutex));
	pthread_mutex_unlock(&(philo->sim_config->forks[fork_2]->mutex));
	log_status(philo, SLEEP_S);
	stop_thread(philo->sim_config->time_to_sleep);
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
