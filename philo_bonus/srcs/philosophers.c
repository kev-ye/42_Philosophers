/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:48:15 by kaye              #+#    #+#             */
/*   Updated: 2021/07/06 20:27:42 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	take_fork(int index, long long start)
{
	const int	left = index;
	const int	right = (index + 1) % singleton()->philo_nbr;

	if (index % 2 == 0)
	{
		sem_wait(singleton()->fork[right].fork);
		print_states(start, singleton()->philo[index].philo_i, FORK);
		sem_wait(singleton()->fork[left].fork);
		print_states(start, singleton()->philo[index].philo_i, FORK);
	}
	else
	{
		sem_wait(singleton()->fork[left].fork);
		print_states(start, singleton()->philo[index].philo_i, FORK);
		sem_wait(singleton()->fork[right].fork);
		print_states(start, singleton()->philo[index].philo_i, FORK);
	}
}

void	drop_fork(int index)
{
	const int	left = index;
	const int	right = (index + 1) % singleton()->philo_nbr;

	if (index % 2 == 0)
	{
		sem_post(singleton()->fork[left].fork);
		sem_post(singleton()->fork[right].fork);
	}
	else
	{
		sem_post(singleton()->fork[right].fork);
		sem_post(singleton()->fork[left].fork);
	}
}

void	eating(int index, long long start)
{
	print_states(start, singleton()->philo[index].philo_i, EAT);
	singleton()->philo[index].last_meal = get_time();
	do_sleep(singleton()->time2[e_EAT]);
}

void	sleeping(int index, long long start)
{
	print_states(start, singleton()->philo[index].philo_i, SLEEP);
	do_sleep(singleton()->time2[e_SLEEP]);
}

void	*philo_in_fork(void *args)
{
	const unsigned int	i = (int)args;

	singleton()->start = get_time();
	while (still_alive() == 0)
	{
		take_fork(i, singleton()->start);
		eating(i, singleton()->start);
		if (singleton()->must_eat != 0
			&& singleton()->philo[i].nbr_eat != singleton()->must_eat)
			eat_counter(i);
		drop_fork(i);
		sleeping(i, singleton()->start);
		print_states(singleton()->start, singleton()->philo[i].philo_i, THINK);
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
	else
		waitpid(singleton()->philo[i].pid, &singleton()->status, 0);
	return (NULL);
}
