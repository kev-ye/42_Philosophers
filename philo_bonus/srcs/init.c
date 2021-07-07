/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:49:55 by kaye              #+#    #+#             */
/*   Updated: 2021/07/07 14:35:14 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	init_philo(void)
{
	int i;

	i = 0;
	singleton()->philo = ft_calloc(sizeof(t_philosophers),
		singleton()->philo_nbr);
	if (!singleton()->philo)
		__exit__(E_MALLOC, FAILURE, TO_FREE, NOTHING);
	while (i < singleton()->philo_nbr)
	{
		singleton()->philo[i].philo_i = i + 1;
		++i;
	}
}

static void	init_fork(void)
{
	int i;

	i = 0;
	singleton()->fork = ft_calloc(sizeof(t_fork),
		singleton()->philo_nbr);
	if (!singleton()->fork)
		__exit__(E_MALLOC, FAILURE, TO_FREE, NOTHING);
	while (i < singleton()->philo_nbr)
	{
		singleton()->fork[i].sem_name = ft_itoa((int)i);
		if (!singleton()->fork[i].sem_name)
			__exit__(E_MALLOC, FAILURE, TO_FREE, TO_CLOSE);
		sem_unlink(singleton()->fork[i].sem_name); // delete after
		singleton()->fork[i].fork = sem_open(singleton()->fork[i].sem_name,
			O_CREAT | O_RDWR,
			0666, 1);
		++i;
	}
	sem_unlink("common"); // delete after
	singleton()->sem_common = sem_open("common", O_CREAT | O_RDWR, 0666, 1);
}

void	init_value(int ac, char **av)
{
	singleton()->philo_nbr = ft_atoi(av[e_NP]);
	init_philo();
	init_fork();
	singleton()->time2[e_DIE] = ft_atoi(av[e_T2D]);
	singleton()->time2[e_EAT] = ft_atoi(av[e_T2E]);
	singleton()->time2[e_SLEEP] = ft_atoi(av[e_T2S]);
	if (av[e_ME])
		singleton()->must_eat = ft_atoi(av[e_ME]);
}

long long	get_time(void)
{
	struct timeval	t;
	long long		ms;

	gettimeofday(&t, NULL);
	ms = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (ms);
}
