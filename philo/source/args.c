/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 23:25:30 by mleonard          #+#    #+#             */
/*   Updated: 2023/10/28 13:05:02 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	validate_args(int argc, char *argv[])
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		printf(ERR_NB_ARGS MSG_USAGE);
		return (ERRNO_NB_ARGS);
	}
	i = 1;
	while (i < argc)
	{
		if (!ft_isnb(argv[i]) || ft_atoi(argv[i]) < 0)
		{
			printf(ERR_TYPE_ARGS MSG_USAGE);
			return (ERRNO_TYPE_ARGS);
		}
		i++;
	}
	if (ft_atoi(argv[NB_PHILOS_POS]) > 250)
	{
		printf(ERR_NB_PHILOS);
		return (ERRNO_NB_PHILOS);
	}
	if (argc == 6 && ft_atoi(argv[MIN_MEALS_POS]) <= 0)
		return (ERRNO_TYPE_ARGS);
	return (NO_ERR);
}

t_sim	*parse_args(int argc, char *argv[])
{
	t_sim	*simulation;

	simulation = (t_sim *)malloc(sizeof(t_sim));
	simulation->has_stopped = FALSE;
	pthread_mutex_init(&(simulation->has_stopped_mutex), NULL);
	simulation->nb_philo = ft_atoi(argv[NB_PHILOS_POS]);
	simulation->time_to_die = ft_atoi(argv[TIME_TO_DIE_POS]);
	simulation->time_to_eat = ft_atoi(argv[TIME_TO_EAT_POS]);
	simulation->time_to_sleep = ft_atoi(argv[TIME_TO_SLEEP_POS]);
	simulation->minimum_meals = -1;
	if (argc == 6)
		simulation->minimum_meals = ft_atoi(argv[MIN_MEALS_POS]);
	simulation->start_time = 0;
	pthread_mutex_init(&(simulation->output_mutex), NULL);
	return (simulation);
}
