/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscasso <tscasso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 18:07:12 by tscasso           #+#    #+#             */
/*   Updated: 2023/11/09 15:53:59 by tscasso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	nb_eat_count(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->nb_ate_lock);
	++philo->nb_eat;
	pthread_mutex_unlock(&philo->sim->nb_ate_lock);
}

int	check_death(t_philo *philo)
{
	int	i;

	pthread_mutex_lock(&philo->sim->death_check_lock);
	i = philo->sim->stop_sim;
	pthread_mutex_unlock(&philo->sim->death_check_lock);
	return (i);
}

size_t	check_meals(t_philo *philo)
{
	size_t	i;

	pthread_mutex_lock(&philo->sim->check_lock);
	i = philo->last_meal;
	pthread_mutex_unlock(&philo->sim->check_lock);
	return (i);
}

int	check_nb_eat(t_philo *philo)
{
	int	i;

	pthread_mutex_lock(&philo->sim->nb_ate_lock);
	i = philo->nb_eat;
	pthread_mutex_unlock(&philo->sim->nb_ate_lock);
	return (i);
}
