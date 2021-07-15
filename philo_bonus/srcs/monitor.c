/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 20:44:42 by kaye              #+#    #+#             */
/*   Updated: 2021/07/15 16:09:26 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	still_alive(void)
{
	singleton()->alive = singleton()->die;
	if (singleton()->alive >= singleton()->philo_nbr)
	{
		sem_post(singleton()->sem_kill);
		return (0);
	}
	return (1);
}

void	*monitoring(void *arg)
{
	const int	i = (int)arg;

	while (1)
	{
		if (singleton()->philo[i].last_meal != 0
			&& get_time() - singleton()->philo[i].last_meal
			> singleton()->time2[e_DIE])
		{
			print_states(singleton()->philo[i].last_meal,
				singleton()->philo[i].philo_i, e_PRINT_DIE);
			sem_wait(singleton()->sem_print);
			singleton()->die = singleton()->philo_nbr;
			break ;
		}
	}
	return (NULL);
}

void	*monitoring_eat(void *args)
{
	int	i;

	(void)args;
	i = 0;
	while (i < singleton()->philo_nbr)
	{
		sem_wait(singleton()->sem_counter);
		++i;
	}
	sem_post(singleton()->sem_kill);
	sem_post(singleton()->sem_print);
	return (NULL);
}
