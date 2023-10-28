/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:51:49 by mleonard          #+#    #+#             */
/*   Updated: 2023/10/28 02:24:00 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

t_sim	*create_philos(t_sim *simulation)
{
	t_philo	**philos;
	size_t	i;

	philos = (t_philo **)malloc(sizeof(t_philo *) * simulation->nb_philo);
	i = 0;
	while (i < simulation->nb_philo)
	{
		philos[i] = (t_philo *)malloc(sizeof(t_philo));
		philos[i]->name = i;
		philos[i]->sim_config = simulation;
		philos[i]->last_meal = 0;
		philos[i]->meal_count = 0;
		pthread_mutex_init(&(philos[i]->last_meal_mutex), NULL);
		i++;
	}
	simulation->philos = philos;
	return (simulation);
}

t_sim	*destroy_philos(t_sim *simulation)
{
	size_t	i;

	i = 0;
	while (i < simulation->nb_philo)
	{
		free(simulation->philos[i]);
		i++;
	}
	free(simulation->philos);
	return (simulation);
}

t_sim	*init_philos(t_sim *simulation)
{
	size_t	i;
	t_philo	**philos;

	i = 0;
	philos = simulation->philos;
	if (simulation->nb_philo == 1)
		pthread_create(&(philos[i]->thread), NULL, lone_philo, philos[i]);
	else
	{
		while (i < simulation->nb_philo)
		{
			pthread_create(&(philos[i]->thread), NULL, philo, philos[i]);
			i++;
		}
	}
	return (simulation);
}
