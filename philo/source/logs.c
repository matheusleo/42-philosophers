/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 00:39:58 by mleonard          #+#    #+#             */
/*   Updated: 2023/10/28 00:47:46 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

// TODO: use the enum instead of the macros
// https://www.youtube.com/watch?v=lWzZ2l5n81c
void	log_status(t_philo *philo, int status)
{
	int		philo_id;
	int		should_print;
	t_sim	*sim_config;

	philo_id = philo->name;
	sim_config = philo->sim_config;
	should_print = !has_sim_stopped(sim_config);
	pthread_mutex_lock(&(sim_config->output_mutex));
	if (status == DEATH_S)
		printf(DEATH_MSG, get_rel_timestamp(sim_config), philo_id + 1);
	else if (status == EAT_S && should_print)
		printf(EAT_MSG, get_rel_timestamp(sim_config), philo_id + 1);
	else if (status == SLEEP_S && should_print)
		printf(SLEEP_MSG, get_rel_timestamp(sim_config), philo_id + 1);
	else if (status == THINK_S && should_print)
		printf(THINK_MSG, get_rel_timestamp(sim_config), philo_id + 1);
	else if (status == FORK_S && should_print)
		printf(FORK_MSG, get_rel_timestamp(sim_config), philo_id + 1);
	pthread_mutex_unlock(&(sim_config->output_mutex));
}
