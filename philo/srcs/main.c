/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 14:25:25 by kaye              #+#    #+#             */
/*   Updated: 2021/07/09 19:05:30 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	do_pthread(void)
{
	int	i;

	i = 0;
	while (i < singleton()->philo_nbr)
		pthread_mutex_init(&singleton()->fork[i++], NULL);
	pthread_mutex_init(&singleton()->mutex_common, NULL);
	i = 0;
	while (i < singleton()->philo_nbr)
	{
		if (pthread_create(&singleton()->philo[i].philo,
				NULL, philo, (void *)(intptr_t)i) != 0)
			return ;
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
		if (!ft_strdigit(av[i]))
			return (FAILURE);
		if (av[i][0] == '0' && av[i][1] == '\0')
			return (FAILURE);
		if (ft_atoi(av[i]) > INT32_MAX || ft_atoi(av[i]) < INT32_MIN)
			return (FAILURE);
		++i;
	}
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (__ret__(ERROR_MSG, FAILURE, NOTHING));
	if (FAILURE == args_check(av))
		return (__ret__(ERROR_MSG, FAILURE, NOTHING));
	init_value(av);
	singleton()->start = get_time();
	if (singleton()->start == -1)
		return (__ret__(NULL, FAILURE, TO_FREE));
	do_pthread();
	return (__ret__(NULL, SUCCESS, TO_FREE));
}
