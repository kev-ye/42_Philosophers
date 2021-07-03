/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:48:15 by kaye              #+#    #+#             */
/*   Updated: 2021/07/03 19:07:53 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	take_fork(int index, long long start)
{
	const int left = index;
	const int right = (index + 1) % singleton()->philo_nbr;
	
	if (index % 2 == 0)
	{
		pthread_mutex_lock(&singleton()->fork[right]);
		print_states(start, singleton()->philo[index].n_philo, FORK);
		pthread_mutex_lock(&singleton()->fork[left]);
		print_states(start, singleton()->philo[index].n_philo, FORK);
	}
	else
	{
		pthread_mutex_lock(&singleton()->fork[left]);
		print_states(start, singleton()->philo[index].n_philo, FORK);
		pthread_mutex_lock(&singleton()->fork[right]);
		print_states(start, singleton()->philo[index].n_philo, FORK);
	}
}

static void	drop_fork(int index)
{
	const int left = index;
	const int right = (index + 1) % singleton()->philo_nbr;
	
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
	print_states(start, singleton()->philo[index].n_philo, EAT);
	do_sleep(singleton()->time2[e_EAT]);
}

static void	sleeping(int index, long long start)
{
	print_states(start, singleton()->philo[index].n_philo, SLEEP);
	do_sleep(singleton()->time2[e_SLEEP]);
}

// int	is_alive(void)
// {
// 	const long long	start = get_time();
// }

void	*philo(void *args)
{
	const unsigned int i = (int)args;
	const long long	start = get_time();
	
	while (1)
	{
		take_fork(i, start);
		eating(i, start);
		drop_fork(i);
		sleeping(i, start);
		print_states(start, singleton()->philo[i].n_philo, THINK);
	}
	return (NULL);
}