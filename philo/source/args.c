/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 23:25:30 by mleonard          #+#    #+#             */
/*   Updated: 2023/10/25 00:36:56 by mleonard         ###   ########.fr       */
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
	return (NO_ERR);
}

t_sim	*parse_args(t_sim *simulation, int argc, char *argv[])
{
	simulation->nb_philo = ft_atoi(argv[NB_PHILOS_POS]);
	simulation->time_to_die = ft_atoi(argv[TIME_TO_DIE_POS]);
	simulation->time_to_eat = ft_atoi(argv[TIME_TO_EAT_POS]);
	simulation->time_to_sleep = ft_atoi(argv[TIME_TO_SLEEP_POS]);
	simulation->minimum_meals = ft_atoi(argv[MIN_MEALS_POS]);
	return (simulation);
}
