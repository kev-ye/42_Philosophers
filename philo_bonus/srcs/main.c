/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 14:25:25 by kaye              #+#    #+#             */
/*   Updated: 2021/07/06 20:22:00 by kaye             ###   ########.fr       */
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
		singleton()->fork[i].sem_name = ft_itoa((int)i);
		if (!singleton()->fork[i].sem_name)
			__exit__(E_MALLOC, FAILURE, TO_FREE, TO_CLOSE);
		singleton()->fork[i++].fork = sem_open(sem_name, O_CREAT | O_RDWR, 0666, 1);
		++i;
	}
	singleton()->sem_common = sem_open("common", O_CREAT | O_RDWR, 0666, 1);
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
		return (__exit__(ERROR_MSG, FAILURE, NOTHING, NOTHING));
	if (FAILURE == args_check(av))
		return (__exit__(ERROR_MSG, FAILURE, NOTHING, NOTHING));
	init_value(ac, av);
	do_pthread();
	__exit__(NULL, SUCCESS, TO_FREE, TO_CLOSE);
	return (0);
}
