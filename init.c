/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscasso <tscasso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 18:33:19 by tscasso           #+#    #+#             */
/*   Updated: 2023/11/09 16:14:11 by tscasso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

t_sim	*init_simulation(char **av)
{
	char	**args;
	t_sim	*sim;

	args = av;
	sim = (t_sim *)malloc(sizeof(t_sim));
	sim->nb_philo = ft_atol(*args++);
	sim->die_timeout = ft_atol(*args++);
	sim->eat_time = ft_atol(*args++);
	if (*args)
		sim->max_eat = ft_atol(*args++);
	else
		sim->max_eat = -1;
	sim->philo_ate = 0;
	sim->stop_sim = 0;
	return (sim);
}

t_philo	**init_philo(t_sim *sim)
{
	t_philo	**philo;
	int		i;

	philo = (t_philo **)malloc(sizeof(t_philo) * sim->nb_philo);
	i = -1;
	while (++i < sim->nb_philo)
	{
		philo[i] = (t_philo *)malloc(sizeof(t_philo));
		memset(philo[i], 0, sizeof(t_philo));
		philo[i]->sim = sim;
		philo[i]->philo_id = i;
		philo[i]->nb_eat = 0;
		philo[i]->is_finished = 0;
		philo[i]->r_fork = i;
		philo[i]->l_fork = (i + 1) % sim->nb_philo;
	}
	return (philo);
}

void	init_mutex(t_sim *sim)
{
	int	i;

	i = -1;
	sim->forks = malloc(sizeof(*sim->forks) * (sim->nb_philo));
	while (++i < sim->nb_philo)
		pthread_mutex_init(&sim->forks[i], NULL);
	pthread_mutex_init(&sim->printf_lock, NULL);
	pthread_mutex_init(&sim->check_lock, NULL);
	pthread_mutex_init(&sim->nb_ate_lock, NULL);
	pthread_mutex_init(&sim->death_check_lock, NULL);
}
