/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 20:44:42 by kaye              #+#    #+#             */
/*   Updated: 2021/07/09 15:33:54 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	still_alive(void)
{
	pthread_mutex_lock(&singleton()->mutex_common);
	singleton()->alive = singleton()->die;
	pthread_mutex_unlock(&singleton()->mutex_common);
	if (singleton()->alive >= singleton()->philo_nbr)
		return (1);
	return (0);
}

void	died(void)
{
	pthread_mutex_lock(&singleton()->mutex_common);
	singleton()->die = singleton()->philo_nbr;
	pthread_mutex_unlock(&singleton()->mutex_common);
}

void	eat_counter(int index)
{
	++singleton()->philo[index].nbr_eat;
	if (singleton()->philo[index].nbr_eat == singleton()->must_eat)
	{
		pthread_mutex_lock(&singleton()->mutex_common);
		++singleton()->die;
		pthread_mutex_unlock(&singleton()->mutex_common);
	}
}

void	monitor(void)
{
	int			index;
	long long	dead;

	while (still_alive() == 0)
	{
		index = 0;
		while (index < singleton()->philo_nbr)
		{
			dead = get_time() - singleton()->philo[index].last_meal;
			if (singleton()->philo[index].last_meal != 0
				&& dead > singleton()->time2[e_DIE])
			{
				print_states(singleton()->philo[index].last_meal,
					singleton()->philo[index].philo_i, DIE);
				died();
				break ;
			}
			++index;
		}
	}
}
