/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 00:39:58 by mleonard          #+#    #+#             */
/*   Updated: 2023/10/27 02:23:37 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

// TODO: use the enum instead of the macros
// https://www.youtube.com/watch?v=lWzZ2l5n81c
void	log_status(t_sim *sim, int status, int philo_id)
{
	pthread_mutex_lock(&(sim->output_mutex));
	if (status == DEATH_S)
		printf(DEATH_MSG, get_rel_timestamp(sim), philo_id + 1);
	else if (status == EAT_S)
		printf(EAT_MSG, get_rel_timestamp(sim), philo_id + 1);
	else if (status == SLEEP_S)
		printf(SLEEP_MSG, get_rel_timestamp(sim), philo_id + 1);
	else if (status == THINK_S)
		printf(THINK_MSG, get_rel_timestamp(sim), philo_id + 1);
	else if (status == FORK_S)
		printf(FORK_MSG, get_rel_timestamp(sim), philo_id + 1);
	pthread_mutex_unlock(&(sim->output_mutex));
}
