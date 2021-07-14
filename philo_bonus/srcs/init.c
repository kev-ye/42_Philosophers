/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 16:49:55 by kaye              #+#    #+#             */
/*   Updated: 2021/07/14 20:10:08 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

const int	g_flag = O_CREAT | O_RDWR;
const int	g_priv = 0666;

static void	init_philo(void)
{
	int	i;

	i = 0;
	singleton()->philo = ft_calloc(sizeof(t_philosophers),
		singleton()->philo_nbr);
	if (!singleton()->philo)
	{
		printf("Malloc error: %s: %d\n", __FILE__, __LINE__);
		__exit__(NULL, FAILURE, TO_FREE, NOTHING);
	}
	while (i < singleton()->philo_nbr)
	{
		singleton()->philo[i].philo_i = i + 1;
		++i;
	}
}

static void	init_fork(void)
{
	singleton()->sem_fork = __sem_open__(S_FORK,
		g_flag,
		g_priv,
		singleton()->philo_nbr);
	singleton()->sem_kill = __sem_open__(S_KILL, g_flag, g_priv, 0);
	singleton()->sem_philo_must_eat_counter = __sem_open__(S_PMEC,
		g_flag,
		g_priv,
		0);
	singleton()->sem_die = __sem_open__(S_DIE, g_flag, g_priv, 1);
	singleton()->sem_print = __sem_open__(S_PRINT, g_flag, g_priv, 1);
}

void	init_value(char **av)
{
	singleton()->philo_nbr = ft_atoi(av[e_NP]);
	init_philo();
	init_fork();
	singleton()->time2[e_DIE] = ft_atoi(av[e_T2D]);
	singleton()->time2[e_EAT] = ft_atoi(av[e_T2E]);
	singleton()->time2[e_SLEEP] = ft_atoi(av[e_T2S]);
	if (av[e_ME] && singleton()->philo_nbr != 1)
		singleton()->must_eat = ft_atoi(av[e_ME]);
}

long long	get_time(void)
{
	struct timeval	t;
	long long		ms;

	if (gettimeofday(&t, NULL) == -1)
	{
		printf("Time error: %s: %d\n", __FILE__, __LINE__);
		return (-1);
	}
	ms = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (ms);
}
