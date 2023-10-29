/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/29 00:55:51 by mleonard          #+#    #+#             */
/*   Updated: 2023/10/29 00:58:20 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	init_sim(t_sim *simulation)
{
	size_t	i;

	i = 0;
	create_forks(simulation);
	create_philos(simulation);
	init_philos(simulation);
	if (simulation->nb_philo > 1)
		init_monitor(simulation);
	pthread_mutex_lock(&(simulation->start_time_mutex));
	simulation->start_time = get_current_time();
	pthread_mutex_unlock(&(simulation->start_time_mutex));
	while (i < simulation->nb_philo)
	{
		pthread_join(simulation->philos[i]->thread, NULL);
		i++;
	}
	pthread_join(simulation->monitor, NULL);
	return (NO_ERR);
}

int	end_sim(t_sim *simulation)
{
	destroy_forks(simulation);
	destroy_philos(simulation);
	free(simulation);
	return (NO_ERR);
}

int	has_sim_stopped(t_sim *simulation)
{
	int	status;

	pthread_mutex_lock(&(simulation->has_stopped_mutex));
	status = simulation->has_stopped;
	pthread_mutex_unlock(&(simulation->has_stopped_mutex));
	return (status);
}

int	set_sim_stop(t_sim *simulation)
{
	pthread_mutex_lock(&(simulation->has_stopped_mutex));
	simulation->has_stopped = TRUE;
	pthread_mutex_unlock(&(simulation->has_stopped_mutex));
	return (simulation->has_stopped);
}
