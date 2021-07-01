/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 14:25:25 by kaye              #+#    #+#             */
/*   Updated: 2021/07/01 19:53:24 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int args_check(char **av)
{
	int i;

	i = 1;
	while (av[i])
	{
		if (!ft_strdigit(av[i++]))
			return (FAILURE);
	}
	return (SUCCESS);
}

void	eat_spaghetti(int index)
{
	long long start;
	const int left = index;
	const int right = (index + 1) % singleton()->philo_nbr;

	start = get_time();
	while (1)
	{
		if (TRY_TAKE_FORK == singleton()->philo[index].philo_status)
		{
			print_states(start, singleton()->philo[index].n_philo, FORK);
			print_states(start, singleton()->philo[index].n_philo, FORK);
			singleton()->philo[index].philo_status = EATING_STATUS;
			pthread_mutex_lock(&singleton()->fork[left].mutex);
			pthread_mutex_lock(&singleton()->fork[right].mutex);
		}
		else if (EATING_STATUS == singleton()->philo[index].philo_status)
		{
			pthread_mutex_unlock(&singleton()->fork[right].mutex);
			pthread_mutex_unlock(&singleton()->fork[left].mutex);
			print_states(start, singleton()->philo[index].n_philo, EAT);
			do_sleep(singleton()->time2eat);
			singleton()->philo[index].philo_status = SLEEPING_STATUS;
		}
		else if (SLEEPING_STATUS == singleton()->philo[index].philo_status)
		{
			print_states(start, singleton()->philo[index].n_philo, SLEEP);
			do_sleep(singleton()->time2sleep);
			singleton()->philo[index].philo_status = THINKING_STATUS;
		}
		else
		{
			print_states(start, singleton()->philo[index].n_philo, THINK);
			singleton()->philo[index].philo_status = TRY_TAKE_FORK;
		}
	}
}

void	*philo(void *args)
{
	const unsigned int i = (int)args;
	
	eat_spaghetti(i);
	return (NULL);
}

void	do_pthread(void)
{
	unsigned int i;

	i = 0;
	while (i < singleton()->philo_nbr)
		pthread_mutex_init(&singleton()->fork[i++].mutex, NULL);
	i = 0;
	while (i < singleton()->philo_nbr)
	{
		pthread_create(&singleton()->philo[i].philo, NULL, philo, (void *)(intptr_t)i);
		++i;
	}
	i = 0;
	while (i < singleton()->philo_nbr)
		pthread_join(singleton()->philo[i++].philo, NULL);
	i = 0;
	while (i < singleton()->philo_nbr)
		pthread_mutex_destroy(&singleton()->fork[i++].mutex);
}

int main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (__ret__(ERROR_MSG, FAILURE, NOTHING));
	if (FAILURE == args_check(av))
		return (__ret__(ERROR_MSG, FAILURE, NOTHING));
	get_value(ac, av);
	init_value();
	do_pthread();
	return (__ret__(NULL, SUCCESS, TO_FREE));
}
