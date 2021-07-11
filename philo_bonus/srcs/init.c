/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:49:55 by kaye              #+#    #+#             */
/*   Updated: 2021/07/11 14:12:15 by kaye             ###   ########.fr       */
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
	sem_unlink("fork");
	singleton()->fork = sem_open("fork", O_CREAT | O_RDWR, 0666, singleton()->philo_nbr);
	sem_unlink("common");
	singleton()->sem_common = sem_open("common", O_CREAT | O_RDWR, 0666, 1);
}

void	init_value(char **av)
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

	if (gettimeofday(&t, NULL) == -1)
	{
		printf("GET TIME ERROE\n");
		return (-1);
	}
	ms = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (ms);
}
