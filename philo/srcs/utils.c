/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 19:19:31 by kaye              #+#    #+#             */
/*   Updated: 2021/07/07 14:38:02 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	__ret__(char *msg, int ret, int to_free)
{
	if (msg)
		printf("%s\n", msg);
	if (TO_FREE == to_free)
	{
		if (singleton())
		{
			free(singleton()->philo);
			singleton()->philo = NULL;
			free(singleton()->fork);
			singleton()->fork = NULL;
		}
		free(singleton());
	}
	return (ret);
}

t_philo	*singleton(void)
{
	static t_philo	*philo = NULL;

	if (!philo)
	{
		philo = ft_calloc(sizeof(t_philo), 1);
		if (!philo)
			return (NULL);
	}
	return (philo);
}

void	do_sleep(long long ms)
{
	const long long	start = get_time();

	while (get_time() - start < ms && still_alive() == 0)
		usleep(499);
}

void	print_states(long long start, int index, char *status)
{
	if (still_alive() != 0)
		return ;
	printf("[%lld] [%u] [%s]\n", get_time() - start, index, status);
}
