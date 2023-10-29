/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 20:34:18 by mleonard          #+#    #+#             */
/*   Updated: 2023/10/29 06:38:59 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

time_t	get_start_time(t_sim *simulation)
{
	time_t	now;

	pthread_mutex_lock(&(simulation->start_time_mutex));
	now = simulation->start_time;
	pthread_mutex_unlock(&(simulation->start_time_mutex));
	return (now);
}

time_t	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
