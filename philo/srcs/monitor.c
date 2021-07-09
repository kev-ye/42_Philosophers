/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 20:44:42 by kaye              #+#    #+#             */
/*   Updated: 2021/07/09 19:04:34 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	still_alive(void)
{
	pthread_mutex_lock(&singleton()->mutex_common);
	singleton()->alive = singleton()->die;
	if (singleton()->alive >= singleton()->philo_nbr)
	{
		pthread_mutex_unlock(&singleton()->mutex_common);
		return (0);
	}
	pthread_mutex_unlock(&singleton()->mutex_common);
	return (1);
}

void	monitor(void)
{
	int			index;

	while (still_alive())
	{
		index = 0;
		while (index < singleton()->philo_nbr)
		{
			if (singleton()->philo[index].last_meal != 0
				&& get_time() - singleton()->philo[index].last_meal
				> singleton()->time2[e_DIE])
			{
				print_states(singleton()->philo[index].last_meal,
					singleton()->philo[index].philo_i, DIE);
				pthread_mutex_lock(&singleton()->mutex_common);
				singleton()->die = singleton()->philo_nbr;
				pthread_mutex_unlock(&singleton()->mutex_common);
				break ;
			}
			++index;
		}
	}
}
