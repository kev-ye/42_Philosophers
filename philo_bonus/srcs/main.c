/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 14:25:25 by kaye              #+#    #+#             */
/*   Updated: 2021/07/12 18:58:34 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*monitoring(void *args)
{
	(void)args;
	int i;

	i = 0;
	while (i < singleton()->philo_nbr)
	{
		sem_wait(singleton()->philo_must_eat_counter);
		++i;
	}
	sem_post(singleton()->sem_kill);
	return (NULL);
}

static void	do_fork(void)
{
	pthread_t	monitor;
	int 		i;

	i = 0;
	pthread_create(&monitor, NULL, monitoring, NULL);
	while (i < singleton()->philo_nbr)
	{
		singleton()->philo[i].pid = fork();
		if (singleton()->philo[i].pid < 0)
			__exit__(E_FORK, FAILURE, TO_FREE, TO_CLOSE);
		else if (singleton()->philo[i].pid == 0)
			philo((void *)(intptr_t)i);
		++i;
	}
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

void	kill_philo(void)
{
	int i;

	i = 0;
	while (i < singleton()->philo_nbr)
	{
		// printf("killing id : [%d]\n", singleton()->philo[i].philo_i);
		kill(singleton()->philo[i].pid, SIGQUIT);
		++i;
	}
}

int	main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (__exit__(ERROR_MSG, FAILURE, NOTHING, NOTHING));
	if (FAILURE == args_check(av))
		return (__exit__(ERROR_MSG, FAILURE, NOTHING, NOTHING));
	init_value(av);
	singleton()->start = get_time();
	if (singleton()->start == -1)
		__exit__(NULL, SUCCESS, TO_FREE, TO_CLOSE);
	do_fork();
	sem_wait(singleton()->sem_kill);
	kill_philo();
	__exit__(NULL, SUCCESS, TO_FREE, TO_CLOSE);
	return (0);
}
