/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscasso <tscasso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:09:33 by tscasso           #+#    #+#             */
/*   Updated: 2023/11/08 18:16:40 by tscasso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	psleep(size_t ms)
{
	size_t	start;

	start = get_time();
	while (get_time() - start < ms)
		usleep(100);
}

int	ft_is_digit(char *c)
{
	char	*p;

	p = c;
	while (*p)
	{
		if (!((*p >= '0' && *p <= '9') || (*p == '+' && *(p + 1) != '+')))
			return (0);
		p++;
	}
	return (1);
}

long	ft_atol(char *s)
{
	int		sign;
	long	out;

	out = 0;
	sign = -1;
	while (*s == ' ' || *s == '\r' || *s == '\t')
		++s;
	if (*s == '-' && ++s)
		sign = 1;
	else if (*s == '+')
		++s;
	while (*s >= '0' && *s <= '9')
		out = out * 10 - (*s++ - '0');
	return (sign * out);
}
