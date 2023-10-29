/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 23:12:52 by mleonard          #+#    #+#             */
/*   Updated: 2023/10/29 05:47:37 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

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
