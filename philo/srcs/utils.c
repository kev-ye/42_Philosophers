/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 19:19:31 by kaye              #+#    #+#             */
/*   Updated: 2021/06/30 19:50:38 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	__ret__(char *msg, int ret)
{
    if (msg)
        ft_putstr(msg);
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

void	free_all(void)
{
	int i;

	i = 0;
	if (singleton())
	{
		free(singleton()->philo);
		singleton()->philo = NULL;
		free(singleton()->fork);
		singleton()->fork = NULL;
	}
	free(singleton());
}

void	print_value(void)
{
	int i;

	i = 0;
	printf("nbr of philo [%u]\n", singleton()->philo_nbr);
	while (i < singleton()->philo_nbr)
	{
		if (i + 1 == singleton()->philo_nbr)
			printf("philo: [%u - %u]\n", singleton()->philo[i].n_philo, singleton()->philo[i].philo_status);
		else if (i < singleton()->philo_nbr)
			printf("philo: [%u - %u]; ", singleton()->philo[i].n_philo, singleton()->philo[i].philo_status);
		++i;
	}
	i = 0;
	while (i < singleton()->philo_nbr)
	{
		if (i + 1 == singleton()->philo_nbr)
			printf("forks: [%u - %u]\n", singleton()->fork[i].n_fork, singleton()->fork[i].fork_status);
		else if (i < singleton()->philo_nbr)
			printf("forks: [%u - %u]; ", singleton()->fork[i].n_fork, singleton()->fork[i].fork_status);
		++i;
	}
	printf("t2die [%u]\n", singleton()->time2die);
	printf("t2eat [%u]\n", singleton()->time2eat);
	printf("t2sleep [%u]\n", singleton()->time2sleep);
	printf("must_e [%u]\n", singleton()->must_eat);
}
