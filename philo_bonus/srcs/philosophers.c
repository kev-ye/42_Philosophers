/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:48:15 by kaye              #+#    #+#             */
/*   Updated: 2021/07/12 19:00:57 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_fork(int index, long long start)
{
	sem_wait(singleton()->sem_fork);
	print_states(start, singleton()->philo[index].philo_i, e_PRINT_FORK);
	sem_wait(singleton()->sem_fork);
	print_states(start, singleton()->philo[index].philo_i, e_PRINT_FORK);
}

void	drop_fork(void)
{
	sem_post(singleton()->sem_fork);
	sem_post(singleton()->sem_fork);
}

void	eating(int index, long long start)
{
	print_states(start, singleton()->philo[index].philo_i, e_PRINT_EAT);
	singleton()->philo[index].last_meal = get_time();
	do_sleep(singleton()->time2[e_EAT]);
	if (singleton()->must_eat != 0
		&& singleton()->philo[index].nbr_eat != singleton()->must_eat)
	{
		++singleton()->philo[index].nbr_eat;
		if (singleton()->philo[index].nbr_eat == singleton()->must_eat)
			sem_post(singleton()->philo_must_eat_counter);
	}
}

void	sleeping(int index, long long start)
{
	print_states(start, singleton()->philo[index].philo_i, e_PRINT_SLEEP);
	do_sleep(singleton()->time2[e_SLEEP]);
}

void	*monitoring(void *arg)
{
	const int i = (int)arg;

	while (1)
	{
		if (singleton()->philo[i].last_meal != 0
			&& get_time() - singleton()->philo[i].last_meal
			> singleton()->time2[e_DIE])
		{
			sem_wait(singleton()->sem_die);
			print_states(singleton()->philo[i].last_meal,
				singleton()->philo[i].philo_i, e_PRINT_DIE);
			sem_wait(singleton()->sem_print);
			singleton()->die = singleton()->philo_nbr;
			break ;
		}
	}
	return (NULL);
}

void	*philo_in_fork(void *args)
{
	pthread_t monitor;
	const unsigned int	i = (int)args;

	pthread_create(&monitor, NULL, monitoring, (void *)(intptr_t)i);
	while (still_alive())
	{
		take_fork(i, singleton()->start);
		eating(i, singleton()->start);
		drop_fork();
		sleeping(i, singleton()->start);
		print_states(singleton()->start, singleton()->philo[i].philo_i, e_PRINT_THINK);
	}
	return (NULL);
}

void	*philo(void *args)
{
	philo_in_fork(args);
	return (NULL);
}
