/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 19:19:31 by kaye              #+#    #+#             */
/*   Updated: 2021/07/03 19:47:20 by kaye             ###   ########.fr       */
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
	const long long start = get_time();

	while (get_time() - start < ms)
		usleep(400);
}

void	print_states(long long start, int index, char *status)
{
	printf("[%lld] [%u] [%s]\n", get_time() - start, index, status);
}

void	print_value(void)
{
	int i;

	i = 0;
	printf("nbr of philo [%u]\n", singleton()->philo_nbr);
	while (i < singleton()->philo_nbr)
	{
		if (i + 1 == singleton()->philo_nbr)
			printf("philo: [%u]\n", singleton()->philo[i].philo_index);
		else if (i < singleton()->philo_nbr)
			printf("philo: [%u]; ", singleton()->philo[i].philo_index);
		++i;
	}
	printf("t2die [%u]\n", singleton()->time2[e_DIE]);
	printf("t2eat [%u]\n", singleton()->time2[e_EAT]);
	printf("t2sleep [%u]\n", singleton()->time2[e_SLEEP]);
	printf("must_e [%u]\n", singleton()->must_eat);
}
