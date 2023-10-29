/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 23:35:11 by mleonard          #+#    #+#             */
/*   Updated: 2023/10/29 00:13:06 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	check_philos_deaths(t_sim *simulation)
{
	size_t				i;
	unsigned long int	rel_offset;
	size_t				nb_philos;
	t_philo				**philos;

	i = 0;
	nb_philos = simulation->nb_philo;
	philos = simulation->philos;
	while (i < nb_philos)
	{
		pthread_mutex_lock(&(philos[i]->last_meal_mutex));
		rel_offset = get_current_time() - philos[i]->last_meal;
		if (philos[i]->last_meal != 0 && rel_offset >= simulation->time_to_die)
		{
			pthread_mutex_lock(&(simulation->has_stopped_mutex));
			simulation->has_stopped = TRUE;
			pthread_mutex_unlock(&(simulation->has_stopped_mutex));
			log_status(philos[i], DEATH_S);
			pthread_mutex_unlock(&(philos[i]->last_meal_mutex));
			return (++i);
		}
		pthread_mutex_unlock(&(philos[i]->last_meal_mutex));
		i++;
	}
	return (NO_ERR);
}

static int	check_philos_meals(t_sim *simulation)
{
	size_t	i;
	t_philo	**philos;

	i = 0;
	philos = simulation->philos;
	while (i < simulation->nb_philo)
	{
		pthread_mutex_lock(&(philos[i]->last_meal_mutex));
		if (philos[i]->meal_count < simulation->minimum_meals)
		{
			pthread_mutex_unlock(&(philos[i]->last_meal_mutex));
			return (FALSE);
		}
		pthread_mutex_unlock(&(philos[i]->last_meal_mutex));
		i++;
	}
	pthread_mutex_lock(&(simulation->has_stopped_mutex));
	simulation->has_stopped = TRUE;
	pthread_mutex_unlock(&(simulation->has_stopped_mutex));
	return (TRUE);
}

int	has_sim_stopped(t_sim *simulation)
{
	int	status;

	pthread_mutex_lock(&(simulation->has_stopped_mutex));
	status = simulation->has_stopped;
	pthread_mutex_unlock(&(simulation->has_stopped_mutex));
	return (status);
}

void	*monitor(void *data)
{
	t_sim	*simulation;
	int		has_philo_died;
	int		min_meals_eaten;

	simulation = (t_sim *)data;
	while (TRUE)
	{
		if (get_start_time(simulation) == 0)
			continue ;
		has_philo_died = check_philos_deaths(simulation);
		if (has_philo_died)
			break ;
		if (simulation->minimum_meals > 0)
		{
			min_meals_eaten = check_philos_meals(simulation);
			if (min_meals_eaten == TRUE)
				break ;
		}
		usleep(1000);
	}
	return (simulation);
}

t_sim	*init_monitor(t_sim *simulation)
{
	pthread_create(&(simulation->monitor), NULL, monitor, simulation);
	return (simulation);
}
