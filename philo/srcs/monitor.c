/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 20:44:42 by kaye              #+#    #+#             */
/*   Updated: 2021/07/08 18:30:25 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

// int	still_alive(void)
// {
// 	pthread_mutex_lock(&singleton()->mutex_common);
// 	singleton()->alive = singleton()->die;
// 	pthread_mutex_unlock(&singleton()->mutex_common);
// 	if (singleton()->alive >= singleton()->philo_nbr)
// 		return (1);
// 	return (0);
// }

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

// void	monitor(void)
// {
// 	int	index;

// 	while (still_alive() == 0)
// 	{
// 		index = 0;
// 		while (index < singleton()->philo_nbr)
// 		{
// 			if (singleton()->philo[index].last_meal != 0
// 				&& get_time() - singleton()->philo[index].last_meal
// 				> singleton()->time2[e_DIE])
// 			{
// 				print_states(singleton()->philo[index].last_meal,
// 					singleton()->philo[index].philo_i, DIE);
// 				died();
// 				break ;
// 			}
// 			++index;
// 		}
// 	}
// }

int	monitor(int index)
{
	long long is_dead;

	pthread_mutex_lock(&singleton()->mutex_common);
	if (singleton()->die)
	{
		pthread_mutex_unlock(&singleton()->mutex_common);
		return (0);
	}
	pthread_mutex_unlock(&singleton()->mutex_common);
	if (singleton()->philo[index].last_meal != 0)
	{
		is_dead = get_time() - singleton()->philo[index].last_meal;
		if (is_dead > singleton()->time2[e_DIE])
		{
			print_states(singleton()->philo[index].last_meal,
				singleton()->philo[index].philo_i, DIE);
			died();
			return (0);
		}
	}
	return (1);
}

int	must2eat(void)
{
	int	count;
	int	i;

	pthread_mutex_lock(&singleton()->mutex_common);
	pthread_mutex_unlock(&singleton()->mutex_common);
	if (0 == singleton()->time2[e_EAT])
		return (0);
	count = 0;
	i = 0;
	while (i < singleton()->philo_nbr)
	{
		pthread_mutex_lock(&singleton()->mutex_common);
		if (singleton()->philo[i++].nbr_eat >= singleton()->time2[e_EAT])
		{
			pthread_mutex_unlock(&singleton()->mutex_common);
			++count;
		}
		else
			pthread_mutex_unlock(&singleton()->mutex_common);
	}
	return (count == singleton()->philo_nbr);
}
