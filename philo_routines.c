/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routines.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscasso <tscasso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 16:07:40 by tscasso           #+#    #+#             */
/*   Updated: 2023/11/09 15:36:02 by tscasso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	take_forks(t_philo *philo)
{
	if (philo->philo_id % 2 == 1)
	{
		pthread_mutex_lock(&philo->sim->forks[philo->r_fork]);
		pthread_mutex_lock(&philo->sim->forks[philo->l_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->sim->forks[philo->l_fork]);
		pthread_mutex_lock(&philo->sim->forks[philo->r_fork]);
	}
	if (!check_death(philo))
	{
		pthread_mutex_lock(&philo->sim->printf_lock);
		printf("%-5ld Philo %d has taken a fork\n",
			(long)(get_time() - philo->start_time), philo->philo_id + 1);
		printf("%-5ld Philo %d has taken a fork\n",
			(long)get_time() - philo->start_time, philo->philo_id + 1);
		pthread_mutex_unlock(&philo->sim->printf_lock);
	}
}

void	eat_time(t_philo *philo)
{
	take_forks(philo);
	if (!check_death(philo))
	{
		printf("%-5ld Philo %d is eating\n",
			(long)get_time() - philo->start_time, philo->philo_id + 1);
		timeof_last_meal(philo);
		nb_eat_count(philo);
		psleep(philo->sim->eat_time);
	}
	pthread_mutex_unlock(&philo->sim->forks[philo->l_fork]);
	pthread_mutex_unlock(&philo->sim->forks[philo->r_fork]);
}

void	sleep_time(t_philo *philo)
{
	if (!check_death(philo))
	{
		pthread_mutex_lock(&philo->sim->printf_lock);
		printf("%-5ld Philo %d is sleeping\n",
			(long)get_time() - philo->start_time,
			philo->philo_id + 1);
		pthread_mutex_unlock(&philo->sim->printf_lock);
		psleep(philo->sim->sleep_time);
	}
}

void	think_time(t_philo *philo)
{
	if (!check_death(philo))
	{
		pthread_mutex_lock(&philo->sim->printf_lock);
		printf("%-5ld Philo %d is thinking\n",
			(long)get_time() - philo->start_time, philo->philo_id + 1);
		pthread_mutex_unlock(&philo->sim->printf_lock);
		usleep(500);
	}
}

void	die_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->sim->printf_lock);
	printf("%-5ld Philo %d has died\n",
		(long)get_time() - philo->start_time, philo->philo_id + 1);
	pthread_mutex_unlock(&philo->sim->printf_lock);
	init_death(philo);
}
