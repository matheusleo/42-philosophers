/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 20:34:18 by mleonard          #+#    #+#             */
/*   Updated: 2023/10/28 20:40:08 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

unsigned long int	get_start_time(t_sim *simulation)
{

	unsigned long int	now;

	pthread_mutex_lock(&(simulation->start_time_mutex));
	now = simulation->start_time;
	pthread_mutex_unlock(&(simulation->start_time_mutex));
	return (now);
}

unsigned long int	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

unsigned long int	get_rel_timestamp(t_sim *simulation)
{
	unsigned long int	now;
	unsigned long int	diff;

	now = get_current_time();
	diff = now - get_start_time(simulation);
	return (diff);
}
