/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:48:15 by kaye              #+#    #+#             */
/*   Updated: 2021/07/09 19:19:47 by kaye             ###   ########.fr       */
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

void	drop_fork(int index)
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

void	*philo_in_fork(void *args)
{
	const unsigned int	i = (int)args;

	while (still_alive() == 0)
	{
		take_fork(i, singleton()->start);
		eating(i, singleton()->start);
		drop_fork(i);
		sleeping(i, singleton()->start);
		print_states(singleton()->start, singleton()->philo[i].philo_i, THINK);
		singleton()->die = singleton()->philo_nbr;
	}
	return (NULL);
}

void	*philo(void *args)
{
	const unsigned int	i = (int)args;

	singleton()->philo[i].pid = fork();
	if (singleton()->philo[i].pid < 0)
		__exit__(E_MALLOC, FAILURE, TO_FREE, TO_CLOSE);
	if (singleton()->philo[i].pid == 0)
	{
		philo_in_fork(args);
		__exit__(NULL, SUCCESS, TO_FREE, TO_CLOSE);
	}
	return (NULL);
}
