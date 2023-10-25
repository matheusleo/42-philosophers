/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 10:14:46 by mleonard          #+#    #+#             */
/*   Updated: 2023/10/25 10:40:49 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

t_sim	*init_forks(t_sim *simulation)
{
	t_fork	**forks;
	size_t	i;

	forks = (t_fork **)malloc(sizeof(t_fork *) * simulation->nb_philo);
	i = 0;
	while (i < simulation->nb_philo)
	{
		forks[i] = (t_fork *)malloc(sizeof(t_fork));
		forks[i]->fork_name = i + 1;
		i++;
	}
	simulation->forks = forks;
	return (simulation);
}

t_sim	*destroy_forks(t_sim *simulation)
{
	size_t	i;

	i = 0;
	while (i < simulation->nb_philo)
	{
		free(simulation->forks[i]);
		i++;
	}
	free(simulation->forks);
}
