/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 19:19:31 by kaye              #+#    #+#             */
/*   Updated: 2021/07/12 17:12:54 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

#define __MICRO_SEC__ 400

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

	while (get_time() - start < ms && still_alive())
		usleep(__MICRO_SEC__);
}

void	print_states(long long start, int index, int s_index)
{
	const long long	current_time = get_time();
	const char		*states[] = {"is eating", "has taken a fork",
		"is sleeping", "is thinking", "died"};

	if (!still_alive())
		return ;
	printf("[%lld] [%u] [%s]\n", current_time - start, index, states[s_index]);
}
