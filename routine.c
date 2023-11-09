/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscasso <tscasso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 21:23:00 by tscasso           #+#    #+#             */
/*   Updated: 2023/11/09 16:15:18 by tscasso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->death_check_lock);
	philo->sim->stop_sim = 1;
	pthread_mutex_unlock(&philo->sim->death_check_lock);
}

void	timeof_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->check_lock);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->sim->check_lock);
}

void	*only_you(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->forks[philo->r_fork]);
	printf("%-5ld Philo %d has taken a fork\n", get_time() - philo->start_time,
		philo->philo_id + 1);
	pthread_mutex_unlock(&philo->sim->forks[philo->r_fork]);
	return (NULL);
}

int	check_philo(t_philo **philo, t_sim *sim)
{
	int	i;

	i = -1;
	while (++i < sim->nb_philo)
	{
		if (check_meals(philo[i]) != 0
			&& get_time() - philo[i]->last_meal > sim->die_timeout)
		{
			die_time(philo[i]);
			return (1);
		}
		if (!philo[i]->is_finished && check_nb_eat(philo[i]) == sim->max_eat
			&& ++sim->philo_ate)
			++philo[i]->is_finished;
		if (sim->philo_ate == sim->nb_philo)
		{
			init_death(philo[i]);
			return (1);
		}
	}
	return (0);
}

void	*routine(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	philo->start_time = get_time();
	timeof_last_meal(philo);
	if (philo->sim->nb_philo == 1)
		return (only_you(philo));
	if (philo->philo_id % 2 == 1)
		psleep(1);
	while (!check_death(philo))
	{
		eat_time(philo);
		sleep_time(philo);
		think_time(philo);
	}
	return (NULL);
}
