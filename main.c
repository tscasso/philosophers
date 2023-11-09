/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tscasso <tscasso@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 21:08:35 by tscasso           #+#    #+#             */
/*   Updated: 2023/11/09 15:52:45 by tscasso          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_philo(t_philo **ph)
{
	t_philo	**head;

	head = ph;
	while (ph && *ph)
		free(*ph++);
	free(head);
}

void	free_sim(t_sim *sim)
{
	int	i;

	i = -1;
	while (++i < sim->nb_philo)
		pthread_mutex_destroy(&sim->forks[i]);
	free(sim->forks);
	pthread_mutex_destroy(&sim->printf_lock);
	pthread_mutex_destroy(&sim->check_lock);
	pthread_mutex_destroy(&sim->nb_ate_lock);
	pthread_mutex_destroy(&sim->death_check_lock);
	free(sim);
}

size_t	get_time(void)
{
	struct timeval	tv;
	size_t			ms;

	gettimeofday(&tv, NULL);
	ms = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (ms);
}

int	main(int ac, char *av[])
{
	t_philo	**philo;
	t_sim	*sim;
	int		i;

	i = -1;
	if (ac < 5 || ac > 6)
		handle_error(ARGS_NUM_ERROR);
	if (!check_args(++av))
		handle_error(ARGS_ERROR);
	sim = init_simulation(av);
	init_mutex(sim);
	philo = init_philo(sim);
	while (++i < sim->nb_philo)
		pthread_create(&(philo[i]->thread), NULL, routine, philo[i]);
	while (!check_philo(philo, sim))
		psleep(1);
	i = -1;
	while (++i < sim->nb_philo)
		pthread_join((philo[i]->thread), NULL);
	free_philo(philo);
	free_sim(sim);
	return (0);
}
