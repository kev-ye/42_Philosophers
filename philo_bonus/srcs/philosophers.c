/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:48:15 by kaye              #+#    #+#             */
/*   Updated: 2021/07/11 18:37:20 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_fork(int index, long long start)
{
	sem_wait(singleton()->fork);
	print_states(start, singleton()->philo[index].philo_i, FORK);
	sem_wait(singleton()->fork);
	print_states(start, singleton()->philo[index].philo_i, FORK);
}

void	drop_fork(void)
{
	sem_post(singleton()->fork);
	sem_post(singleton()->fork);
}

void	eating(int index, long long start)
{
	print_states(start, singleton()->philo[index].philo_i, EAT);
	singleton()->philo[index].last_meal = get_time();
	do_sleep(singleton()->time2[e_EAT]);
	if (singleton()->must_eat != 0
		&& singleton()->philo[index].nbr_eat != singleton()->must_eat)
	{
		++singleton()->philo[index].nbr_eat;
		if (singleton()->philo[index].nbr_eat == singleton()->must_eat)
		{
			sem_wait(singleton()->sem_common);
			++singleton()->die;
			sem_post(singleton()->sem_common);
		}
	}
}

void	sleeping(int index, long long start)
{
	print_states(start, singleton()->philo[index].philo_i, SLEEP);
	do_sleep(singleton()->time2[e_SLEEP]);
}

void	*monitor2(void *arg)
{
	const int i = (int)arg;

	while (still_alive())
	{
		if (singleton()->philo[i].last_meal != 0
			&& get_time() - singleton()->philo[i].last_meal
			> singleton()->time2[e_DIE])
		{
			print_states(singleton()->philo[i].last_meal,
				singleton()->philo[i].philo_i, DIE);
			sem_wait(singleton()->sem_common);
			singleton()->die = singleton()->philo_nbr;
			sem_post(singleton()->sem_common);
			break ;
		}
	}
	return (NULL);
}

void	*philo_in_fork(void *args)
{
	pthread_t monitor;
	const unsigned int	i = (int)args;

	pthread_create(&monitor, NULL, monitor2, (void *)(intptr_t)i);
	while (still_alive())
	{
		take_fork(i, singleton()->start);
		eating(i, singleton()->start);
		drop_fork();
		sleeping(i, singleton()->start);
		print_states(singleton()->start, singleton()->philo[i].philo_i, THINK);
	}
	sem_post(singleton()->kill_philo);
	return (NULL);
}

void	*philo(void *args)
{
	philo_in_fork(args);
	return (NULL);
}
