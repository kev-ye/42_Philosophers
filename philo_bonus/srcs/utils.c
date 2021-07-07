/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 19:19:31 by kaye              #+#    #+#             */
/*   Updated: 2021/07/06 20:14:49 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_philo	*singleton(void)
{
	static t_philo	*philo = NULL;

	if (!philo)
	{
		philo = ft_calloc(sizeof(t_philo), 1);
		if (!philo)
			__exit__(E_MALLOC, FAILURE, NOTHING, NOTHING);
	}
	return (philo);
}

void	do_sleep(long long ms)
{
	const long long	start = get_time();

	while (get_time() - start < ms)
		usleep(400);
}

void	print_states(long long start, int index, char *status)
{
	if (still_alive() != 0)
		return ;
	printf("[%lld] [%u] [%s]\n", get_time() - start, index, status);
}
