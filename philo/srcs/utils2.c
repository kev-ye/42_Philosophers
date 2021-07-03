/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:49:55 by kaye              #+#    #+#             */
/*   Updated: 2021/07/03 19:47:09 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	get_value(int ac, char **av)
{
	int i;

	i = -1;
	singleton()->philo_nbr = ft_atoi(av[e_NP]);
	singleton()->philo = ft_calloc(sizeof(t_philosophers), singleton()->philo_nbr);
	if (!singleton()->philo)
		return ;
	while (i <= singleton()->philo_nbr)
	{
		singleton()->philo[i].philo_index = i + 1;
		++i;
	}
	singleton()->fork = ft_calloc(sizeof(pthread_mutex_t), singleton()->philo_nbr);
	if (!singleton()->fork)
		return ;
	singleton()->time2[e_DIE] = ft_atoi(av[e_T2D]);
	singleton()->time2[e_EAT] = ft_atoi(av[e_T2E]);
	singleton()->time2[e_SLEEP] = ft_atoi(av[e_T2S]);
	if (av[e_ME])
		singleton()->must_eat = ft_atoi(av[e_ME]);
}

void	init_value(void)
{
	int i;

	if (singleton())
	{
		i = 0;
		while (singleton()->philo && i < singleton()->philo_nbr)
		{
			singleton()->philo[i].philo_index = i + 1;
			++i;
		}
	}
}

long long	get_time(void)
{
	struct timeval	t;
	long long			ms;
	
	gettimeofday(&t, NULL);
	ms = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (ms);
}
