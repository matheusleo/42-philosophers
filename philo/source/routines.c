/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 00:42:29 by mleonard          #+#    #+#             */
/*   Updated: 2023/10/28 02:29:22 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	*lone_philo(void *data)
{
	t_philo	*philo;
	int		id;

	philo = (t_philo *)data;
	id = philo->name;
	pthread_mutex_lock(&(philo->sim_config->forks[id]->mutex));
	log_status(philo, FORK_S);
	pthread_mutex_unlock(&(philo->sim_config->forks[id]->mutex));
	return (NULL);
}

void	*think(t_philo *philo)
{
	int	time_to_think;

	log_status(philo, THINK_S);
	time_to_think = 1;
	stop_thread(time_to_think);
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
	philo->last_meal = get_rel_timestamp(philo->sim_config);
	philo->meal_count++;
	pthread_mutex_unlock(&(philo->last_meal_mutex));
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
	if (id == 0)
		fork_1 = (philo->sim_config->nb_philo) - 1;
	else
		fork_1 = id + (id % 2 - 1);
	fork_2 = id + ((id + 1) % 2 - 1);
	while (!has_sim_stopped(philo->sim_config))
		philo_routine(philo, fork_1, fork_2);
	return (NULL);
}
