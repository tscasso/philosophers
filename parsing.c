/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscasso <tscasso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 22:37:59 by tscasso           #+#    #+#             */
/*   Updated: 2023/11/09 15:31:02 by tscasso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_args(char **av)
{
	char	**args;

	args = av;
	while (*args)
	{
		if (!ft_is_digit(*args) || ft_atol(*args) < 0
			|| ft_atol(*args) > INT_MAX)
			return (0);
		args++;
	}
	return (1);
}
