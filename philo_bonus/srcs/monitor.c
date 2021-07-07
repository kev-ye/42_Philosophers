/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 20:44:42 by kaye              #+#    #+#             */
/*   Updated: 2021/07/06 20:03:43 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	still_alive(void)
{
	sem_wait(singleton()->sem_common);
	singleton()->alive = singleton()->die;
	sem_post(singleton()->sem_common);
	if (singleton()->alive >= singleton()->philo_nbr)
		return (1);
	return (0);
}

void	died(void)
{
	sem_wait(singleton()->sem_common);
	singleton()->die = singleton()->philo_nbr;
	sem_post(singleton()->sem_common);
}

void	eat_counter(int index)
{
	++singleton()->philo[index].nbr_eat;
	if (singleton()->philo[index].nbr_eat == singleton()->must_eat)
	{

		sem_wait(singleton()->sem_common);
		++singleton()->die;

		sem_post(singleton()->sem_common);
	}
}

void	monitor(void)
{
	int	index;

	while (still_alive() == 0)
	{
		index = -1;
		while (++index < singleton()->philo_nbr)
		{
			if (singleton()->philo[index].last_meal != 0
				&& get_time() - singleton()->philo[index].last_meal
				>= singleton()->time2[e_DIE])
			{
				print_states(singleton()->philo[index].last_meal,
					singleton()->philo[index].philo_i, DIE);
				died();
				break ;
			}
		}
	}
}
