/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 00:42:29 by mleonard          #+#    #+#             */
/*   Updated: 2023/10/28 00:48:22 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	*lone_philo(t_philo *philo)
{
	int	id;

	id = philo->name;
	pthread_mutex_lock(&(philo->sim_config->forks[id]->mutex));
	log_status(philo, FORK_S);
	pthread_mutex_unlock(&(philo->sim_config->forks[id]->mutex));
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
	log_status(philo, THINK_S);
}

void	*philo(t_philo *philo)
{
	int		id;
	t_sim	*sim_config;
	int		fork_1;
	int		fork_2;

	id = philo->name;
	sim_config = philo->sim_config;
	if (id == 0)
		fork_1 = sim_config->nb_philo - 1;
	else
		fork_1 = id + (id % 2 - 1);
	fork_2 = id + ((id + 1) % 2 - 1);
	while (!has_sim_stopped(sim_config))
		philo_routine(philo, fork_1, fork_2);
}
