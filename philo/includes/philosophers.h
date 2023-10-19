/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 23:12:49 by mleonard          #+#    #+#             */
/*   Updated: 2023/10/18 23:36:12 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

// Libs
# include <stdio.h> //printf
# include <stdlib.h> //exit

# define TRUE 1
# define FALSE 0
# define MSG_USAGE "Use as:\n \
philo <number_philosophers> <time_to_die> \
<time_to_eat> <time_to_sleep> [minimum_meals]\n"
# define ERR_NB_ARGS "Invalid number of arguments\n"
# define ERR_TYPE_ARGS "Invalid type of arguments\n"

// Args
void	validate_args(int argc, char *argv[]);

// Utility functions
int		ft_isdigit(int c);
int		ft_isnb(char *str);

#endif
