/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:48:15 by kaye              #+#    #+#             */
/*   Updated: 2021/07/15 20:32:50 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	take_fork(int index, long long start)
{
	if (singleton()->philo_nbr != 1)
	{
		sem_wait(singleton()->sem_fork);
		print_states(start, index, e_PRINT_FORK);
	}
	sem_wait(singleton()->sem_fork);
	print_states(start, index, e_PRINT_FORK);
}

static void	drop_fork(void)
{
	sem_post(singleton()->sem_fork);
	sem_post(singleton()->sem_fork);
}

static void	eating(int index, long long start)
{
	if (singleton()->philo_nbr != 1)
		print_states(start, index, e_PRINT_EAT);
	singleton()->philo[index].last_meal = get_time();
	if (singleton()->philo_nbr == 1)
		do_sleep(singleton()->time2[e_DIE], index);
	else
		do_sleep(singleton()->time2[e_EAT], index);
	++singleton()->philo[index].nbr_eat;
	if (singleton()->must_eat != 0
		&& singleton()->philo[index].nbr_eat == singleton()->must_eat)
			sem_post(singleton()->sem_counter);
}

static void	sleeping(int index, long long start)
{
	if (singleton()->philo_nbr != 1)
		print_states(start, index, e_PRINT_SLEEP);
	do_sleep(singleton()->time2[e_SLEEP], index);
}

void	*monitoring_close(void *args)
{
	(void)args;
	sem_wait(singleton()->sem_test);
	__sem_close__();
	return (NULL);
}

void	*philo(void *args)
{
	const unsigned int	i = (int)args;
	// pthread_t			monitor;
	// pthread_t			monitor2;
	int 				j;

	// pthread_create(&monitor, NULL, monitoring, (void *)(intptr_t)i);
	// pthread_create(&monitor2, NULL, monitoring_close, (void *)(intptr_t)i);
	// pthread_detach(monitor);
	// pthread_detach(monitor2);
	while (still_alive(i))
	{
		take_fork(i, singleton()->start);
		eating(i, singleton()->start);
		drop_fork();
		sleeping(i, singleton()->start);
		print_states(singleton()->start, i, e_PRINT_THINK);
		do_sleep(singleton()->time2[e_EAT] - singleton()->time2[e_SLEEP], i);
	}
	j = -1;
	while (++j < singleton()->philo_nbr)
		sem_post(singleton()->sem_counter);
	sem_wait(singleton()->sem_print);
	__exit__(NULL, SUCCESS, NOTHING, NOTHING);
	return (NULL);
}
