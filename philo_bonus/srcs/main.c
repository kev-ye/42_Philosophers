/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 14:25:25 by kaye              #+#    #+#             */
/*   Updated: 2021/07/07 15:29:02 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	do_pthread(void)
{
	unsigned int	i;
	char			*sem_name;

	i = 0;
	while (i < singleton()->philo_nbr)
	{
		pthread_create(&singleton()->philo[i].philo,
			NULL, philo, (void *)(intptr_t)i);
		++i;
	}
	// monitor();
	i = 0;
	while (i < singleton()->philo_nbr)
		pthread_join(singleton()->philo[i++].philo, NULL);
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
		return (__exit__(ERROR_MSG, FAILURE, NOTHING, NOTHING));
	if (FAILURE == args_check(av))
		return (__exit__(ERROR_MSG, FAILURE, NOTHING, NOTHING));
	init_value(ac, av);
	singleton()->start = get_time();
	do_pthread();
	__exit__(NULL, SUCCESS, TO_FREE, TO_CLOSE);
	return (0);
}
