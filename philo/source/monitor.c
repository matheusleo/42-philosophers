/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 23:35:11 by mleonard          #+#    #+#             */
/*   Updated: 2023/10/26 22:07:08 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int check_philos_deaths(t_sim *simulation)
{
	size_t i;
	unsigned long int rel_offset;
	int	nb_philos;
	t_philo	**philos;

	i = 0;
	nb_philos = simulation->nb_philo;
	philos = simulation->philos;
	while (i < nb_philos)
	{
		pthread_mutex_lock(&(philos[i]->last_meal_mutex));
		rel_offset = get_rel_timestamp(philos[i]->sim_config) - philos[i]->last_meal;
		if (rel_offset >= philos[i]->sim_config->time_to_die)
		{
			simulation->should_stop = TRUE;
			// TODO: create function to print the STATUS, TIMESTAMP and PHILO->NAME
			printf("philo [%d] has died at %ldms\n", philos[i]->name, get_rel_timestamp(simulation));
			pthread_mutex_unlock(&(philos[i]->last_meal_mutex));
			return (++i);
		}
		pthread_mutex_unlock(&(philos[i]->last_meal_mutex));
		i++;
	}
	return (NO_ERR);
}

t_sim *monitor(t_sim *simulation)
{
	size_t i;
	int has_philo_died;

	while (TRUE)
	{
		has_philo_died = check_philos_deaths(simulation);
		if (has_philo_died)
			break;
		usleep(1000);
	}
	return (simulation);
}

t_sim	*init_monitor(t_sim *simulation)
{
	pthread_create(&(simulation->monitor), NULL, monitor, simulation);
	pthread_join(simulation->monitor, NULL);
}
