/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 20:44:42 by kaye              #+#    #+#             */
/*   Updated: 2021/07/12 17:06:22 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	still_alive(void)
{
	singleton()->alive = singleton()->die;
	if (singleton()->alive >= singleton()->philo_nbr)
	{
		sem_post(singleton()->sem_kill);
		sem_wait(singleton()->sem_die);
		return (0);
	}
	return (1);
}
