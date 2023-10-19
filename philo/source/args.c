/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 23:25:30 by mleonard          #+#    #+#             */
/*   Updated: 2023/10/18 23:34:52 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	validate_args(int argc, char *argv[])
{
	int	i;

	if (argc != 5 && argc != 6)
	{
		printf(ERR_NB_ARGS MSG_USAGE);
		exit(1);
	}
	i = 1;
	while (i < argc)
	{
		if (!ft_isnb(argv[i]))
		{
			printf(ERR_TYPE_ARGS MSG_USAGE);
			exit(1);
		}
		i++;
	}
}
