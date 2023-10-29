/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 00:39:58 by mleonard          #+#    #+#             */
/*   Updated: 2023/10/28 21:29:42 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

// TODO: use the enum instead of the macros
// https://www.youtube.com/watch?v=lWzZ2l5n81c
void	log_status(t_philo *philo, int status)
{
	int								philo_id;
	int								should_print;
	t_sim							*sim_config;
	unsigned long int	ts;

	philo_id = philo->name;
	sim_config = philo->sim_config;
	should_print = !has_sim_stopped(sim_config);
	ts = get_current_time() - get_start_time(sim_config);
	pthread_mutex_lock(&(sim_config->output_mutex));
	if (status == DEATH_S)
		printf(DEATH_MSG, ts, philo_id + 1);
	else if (status == EAT_S && should_print)
		printf(EAT_MSG, ts, philo_id + 1);
	else if (status == SLEEP_S && should_print)
		printf(SLEEP_MSG, ts, philo_id + 1);
	else if (status == THINK_S && should_print)
		printf(THINK_MSG, ts, philo_id + 1);
	else if (status == FORK_S && should_print)
		printf(FORK_MSG, ts, philo_id + 1);
	pthread_mutex_unlock(&(sim_config->output_mutex));
}
