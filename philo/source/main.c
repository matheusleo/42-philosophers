/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 23:12:52 by mleonard          #+#    #+#             */
/*   Updated: 2023/10/28 21:36:03 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

static int	init_sim(t_sim *simulation)
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

static int	end_sim(t_sim *simulation)
{
	destroy_forks(simulation);
	destroy_philos(simulation);
	free(simulation);
	return (NO_ERR);
}

int	main(int argc, char *argv[])
{
	t_sim	*simulation;
	int		err;

	simulation = NULL;
	err = validate_args(argc, argv);
	if (err)
		return (err);
	simulation = parse_args(argc, argv);
	init_sim(simulation);
	end_sim(simulation);
}
