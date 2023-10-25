/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mleonard <mleonard@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 23:12:52 by mleonard          #+#    #+#             */
/*   Updated: 2023/10/25 00:38:19 by mleonard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int main(int argc, char *argv[])
{
	t_sim simulation;
	int err;

	err = validate_args(argc, argv);
	if (err)
		return (err);
	parse_args(&simulation, argc, argv);
}
