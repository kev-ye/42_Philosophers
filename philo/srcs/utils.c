/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 19:19:31 by kaye              #+#    #+#             */
/*   Updated: 2021/07/01 19:52:33 by kaye             ###   ########.fr       */
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

void	get_value(int ac, char **av)
{
	int i;

	i = -1;
	singleton()->philo_nbr = ft_atoi(av[NBR_PHILO]);
	singleton()->philo = ft_calloc(sizeof(t_philosophers), singleton()->philo_nbr);
	if (!singleton()->philo)
		return ;
	while (i <= singleton()->philo_nbr)
	{
		singleton()->philo[i].n_philo = i + 1;
		++i;
	}
	singleton()->fork = ft_calloc(sizeof(t_fork), singleton()->philo_nbr);
	if (!singleton()->fork)
		return ;
	singleton()->time2die = ft_atoi(av[T2D]);
	singleton()->time2eat = ft_atoi(av[T2E]);
	singleton()->time2sleep = ft_atoi(av[T2S]);
	if (av[MUST_E])
		singleton()->must_eat = ft_atoi(av[MUST_E]);
}

void	init_value(void)
{
	int i;

	if (singleton())
	{
		i = 0;
		while (singleton()->philo && i < singleton()->philo_nbr)
		{
			singleton()->philo[i].n_philo = i + 1;
			singleton()->philo[i].philo_status = TRY_TAKE_FORK;
			++i;
		}
		i = 0;
		while (singleton()->fork && i < singleton()->philo_nbr)
		{
			singleton()->fork[i].fork_status = FORK_IS_DROP;
			++i;
		}
	}
}

void	do_sleep(long long ms)
{
	const long long start = get_time();

	while (get_time() - start < ms)
		usleep(500);
}

long long	get_time(void)
{
	struct timeval	t;
	long long			ms;
	
	gettimeofday(&t, NULL);
	ms = (t.tv_sec * 1000) + (t.tv_usec / 1000);
	return (ms);
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
			printf("philo: [%u - %u]\n", singleton()->philo[i].n_philo, singleton()->philo[i].philo_status);
		else if (i < singleton()->philo_nbr)
			printf("philo: [%u - %u]; ", singleton()->philo[i].n_philo, singleton()->philo[i].philo_status);
		++i;
	}
	printf("t2die [%u]\n", singleton()->time2die);
	printf("t2eat [%u]\n", singleton()->time2eat);
	printf("t2sleep [%u]\n", singleton()->time2sleep);
	printf("must_e [%u]\n", singleton()->must_eat);
}
