/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:48:15 by kaye              #+#    #+#             */
/*   Updated: 2021/07/09 19:05:54 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	take_fork(int index, long long start)
{
	const int	left = index;
	const int	right = (index + 1) % singleton()->philo_nbr;

	if (index % 2 == 0)
	{
		if (singleton()->philo_nbr != 1)
		{
			pthread_mutex_lock(&singleton()->fork[right]);
			print_states(start, singleton()->philo[index].philo_i, FORK);
		}
		pthread_mutex_lock(&singleton()->fork[left]);
		print_states(start, singleton()->philo[index].philo_i, FORK);
	}
	else
	{
		pthread_mutex_lock(&singleton()->fork[left]);
		print_states(start, singleton()->philo[index].philo_i, FORK);
		pthread_mutex_lock(&singleton()->fork[right]);
		print_states(start, singleton()->philo[index].philo_i, FORK);
	}
}

static void	drop_fork(int index)
{
	const int	left = index;
	const int	right = (index + 1) % singleton()->philo_nbr;

	if (index % 2 == 0)
	{
		pthread_mutex_unlock(&singleton()->fork[left]);
		pthread_mutex_unlock(&singleton()->fork[right]);
	}
	else
	{
		pthread_mutex_unlock(&singleton()->fork[right]);
		pthread_mutex_unlock(&singleton()->fork[left]);
	}
}

static void	eating(int index, long long start)
{
	if (singleton()->philo_nbr != 1)
		print_states(start, singleton()->philo[index].philo_i, EAT);
	singleton()->philo[index].last_meal = get_time();
	do_sleep(singleton()->time2[e_EAT]);
	if (singleton()->must_eat != 0
		&& singleton()->philo[index].nbr_eat != singleton()->must_eat)
	{
		++singleton()->philo[index].nbr_eat;
		if (singleton()->philo[index].nbr_eat == singleton()->must_eat)
		{
			pthread_mutex_lock(&singleton()->mutex_common);
			++singleton()->die;
			pthread_mutex_unlock(&singleton()->mutex_common);
		}
	}
}

static void	sleeping(int index, long long start)
{
	if (singleton()->philo_nbr != 1)
		print_states(start, singleton()->philo[index].philo_i, SLEEP);
	do_sleep(singleton()->time2[e_SLEEP]);
}

void	*philo(void *args)
{
	const unsigned int	i = (int)args;

	while (still_alive())
	{
		take_fork(i, singleton()->start);
		eating(i, singleton()->start);
		drop_fork(i);
		sleeping(i, singleton()->start);
		if (singleton()->philo_nbr != 1)
			print_states(
				singleton()->start,
				singleton()->philo[i].philo_i,
				THINK);
	}
	return (NULL);
}
