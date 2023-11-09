/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscasso <tscasso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 21:43:44 by tscasso           #+#    #+#             */
/*   Updated: 2023/11/09 16:13:09 by tscasso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	handle_error(short error_code)
{
	if (error_code == ARGS_ERROR)
		printf("Argument is not a digit "
			"or it overflows int "
			"or it is negative "
			"or have two plus signs\n");
	else if (error_code == ARGS_NUM_ERROR)
		printf("Wrong number of arguments\n");
	exit(1);
}
