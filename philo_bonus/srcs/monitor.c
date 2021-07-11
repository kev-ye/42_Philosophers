/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 20:44:42 by kaye              #+#    #+#             */
/*   Updated: 2021/07/11 20:07:16 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	still_alive(void)
{
	sem_wait(singleton()->sem_common);
	singleton()->alive = singleton()->die;
	if (singleton()->alive >= singleton()->philo_nbr)
	{
		// sem_post(singleton()->sem_common);
		sem_post(singleton()->kill_philo);
		return (0);
	}
	sem_post(singleton()->sem_common);
	return (1);
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
// 				sem_wait(singleton()->sem_common);
// 				singleton()->die = singleton()->philo_nbr;
// 				sem_post(singleton()->sem_common);
// 				break ;
// 			}
// 			++index;
// 		}
// 	}
// }
