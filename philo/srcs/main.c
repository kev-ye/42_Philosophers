/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 14:25:25 by kaye              #+#    #+#             */
/*   Updated: 2021/07/04 17:07:54 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	do_pthread(void)
{
	unsigned int	i;

	i = 0;
	while (i < singleton()->philo_nbr)
		pthread_mutex_init(&singleton()->fork[i++], NULL);
	pthread_mutex_init(&singleton()->mutex_common, NULL);
	i = 0;
	while (i < singleton()->philo_nbr)
	{
		pthread_create(&singleton()->philo[i].philo,
			NULL, philo, (void *)(intptr_t)i);
		++i;
	}
	monitor();
	i = 0;
	while (i < singleton()->philo_nbr)
		pthread_join(singleton()->philo[i++].philo, NULL);
	i = 0;
	while (i < singleton()->philo_nbr)
		pthread_mutex_destroy(&singleton()->fork[i++]);
	pthread_mutex_destroy(&singleton()->mutex_common);
}

static int	args_check(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (!ft_strdigit(av[i++]))
			return (FAILURE);
	}
	if (ft_atoi(av[1]) < 2)
		return (FAILURE);
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (__ret__(ERROR_MSG, FAILURE, NOTHING));
	if (FAILURE == args_check(av))
		return (__ret__(ERROR_MSG, FAILURE, NOTHING));
	init_value(ac, av);
	do_pthread();
	return (__ret__(NULL, SUCCESS, TO_FREE));
}
