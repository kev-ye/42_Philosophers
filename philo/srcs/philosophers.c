/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 14:25:25 by kaye              #+#    #+#             */
/*   Updated: 2021/06/30 20:18:01 by kaye             ###   ########.fr       */
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
			return (ERROR);
	}
	return (SUCCESS);
}

static void	get_value(int ac, char **av)
{
	int i;

	i = -1;
	singleton()->philo_nbr = ft_atoi(av[NBR_PHILO]);
	singleton()->philo = ft_calloc(sizeof(t_philosophers), singleton()->philo_nbr);
	if (!singleton()->philo)
		return ;
	while (++i <= singleton()->philo_nbr)
		singleton()->philo[i].n_philo = i + 1;
	singleton()->fork = ft_calloc(sizeof(t_fork), singleton()->philo_nbr);
	if (!singleton()->fork)
		return ;
	singleton()->time2die = ft_atoi(av[T2D]);
	singleton()->time2eat = ft_atoi(av[T2E]);
	singleton()->time2sleep = ft_atoi(av[T2S]);
	if (av[MUST_E])
		singleton()->must_eat = ft_atoi(av[MUST_E]);
}

void	init_value(void)
{
	int i;

	if (singleton())
	{
		i = 0;
		while (singleton()->philo && i < singleton()->philo_nbr)
		{
			singleton()->philo[i].n_philo = i + 1;
			singleton()->philo[i].philo_status = NO_STATUS;
			// singleton()->philo[i].left_fork = DROP_FORK;
			// singleton()->philo[i].right_fork = DROP_FORK;
			++i;
		}
		i = 0;
		while (singleton()->fork && i < singleton()->philo_nbr)
		{
			singleton()->fork[i].n_fork = i + 1;
			singleton()->fork[i].fork_status = FORK_IS_DROP;
			++i;
		}
	}
}

long	get_time(void)
{
	struct timeval	t;
	long			ms;
	
	gettimeofday(&t, NULL);
	ms = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (ms);
}

void	*philo(void *args)
{
	const unsigned int i = (int)args;
	long start;
	long count;

	start = get_time();
	while (1)
	{
		if (FORK_IS_DROP == singleton()->fork[L_FORK].fork_status
			&& FORK_IS_DROP == singleton()->fork[R_FORK].fork_status)
		{
			pthread_mutex_lock(&singleton()->mutex);
			singleton()->fork[L_FORK].fork_status = FORK_IS_TAKE;
			printf("TS: [%ld] -- PHILO: [%u] (LEFT)-- "FORK, get_time() - start, singleton()->philo[i].n_philo);
			singleton()->fork[R_FORK].fork_status = FORK_IS_TAKE;
			printf("TS: [%ld] -- PHILO: [%u] (RIGHT)-- "FORK, get_time() - start, singleton()->philo[i].n_philo);
			singleton()->philo[i].philo_status = EATING_STATUS;
			printf("TS: [%ld] -- PHILO: [%u] -- "EAT, get_time() - start, singleton()->philo[i].n_philo);
			count = 0;
			while (count != singleton()->time2eat)
			{
				// printf("c : [%lu] t : [%u]\n", count, singleton()->time2eat);
				usleep(1000);
				++count;
			}
			singleton()->fork[L_FORK].fork_status = FORK_IS_DROP;
			singleton()->fork[R_FORK].fork_status = FORK_IS_DROP;
			pthread_mutex_unlock(&singleton()->mutex);
		}
		else
		{
			count = 0;
			singleton()->philo[i].philo_status = THINKING_STATUS;
			printf("TS: [%ld] -- PHILO: [%u] -- "THINK, get_time() - start, singleton()->philo[i].n_philo);
			while (FORK_IS_TAKE == singleton()->fork[L_FORK].fork_status
			&& FORK_IS_TAKE == singleton()->fork[R_FORK].fork_status)
			{
				usleep(1000);
				++count;
				if (count == singleton()->time2die)
					break ;
			}
		}
		if (EATING_STATUS == singleton()->philo[i].philo_status)
		{
			printf("TS: [%ld] -- PHILO: [%u] -- "SLEEP, get_time() - start, singleton()->philo[i].n_philo);
			count = 0;
			while (count != singleton()->time2sleep)
			{
				usleep(1000);
				++count;
			}
		}
	}
	printf("TS: [%ld] -- PHILO: [%u] -- "EAT, start, singleton()->philo[i].n_philo);
	

	///// test
	// start = get_time();

	// pthread_mutex_lock(&singleton()->mutex);
	// printf("->0 : [%ld]\n", get_time() - start);

	// usleep(1000 * 10);
	// printf("->1 : [%ld]\n", get_time() - start);

	// usleep(1000 * 100);
	// printf("->2 : [%ld]\n", get_time() - start);

	// usleep(1000 * 1000);
	// printf("->2 : [%ld]\n", get_time() - start);

	return (NULL);
}

void	do_pthread(void)
{
	unsigned int i;

	i = 0;
	pthread_mutex_init(&singleton()->mutex, NULL);
	while (i < singleton()->philo_nbr)
	{
		pthread_create(&singleton()->philo[i].philo, NULL, philo, (void *)(intptr_t)i);
		++i;
	}
	i = 0;
	while (i < singleton()->philo_nbr)
	{
		pthread_join(singleton()->philo[i].philo, NULL);
		++i;
	}
	pthread_mutex_destroy(&singleton()->mutex);
}

int main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (__ret__(ERROR_MSG, ERROR));
	if (ERROR == args_check(av))
		return (__ret__(ERROR_MSG, ERROR));
	get_value(ac, av);
	init_value();
	do_pthread();
	// print_value();
	free_all();
	return (SUCCESS);
}
