/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 19:19:31 by kaye              #+#    #+#             */
/*   Updated: 2021/07/13 10:57:23 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

#define __MICRO_SEC__ 400

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

sem_t	*__sem_open__(const char *to_create, int flag, int priv, int lock)
{
	sem_t	*new_sem;

	sem_unlink(to_create);
	new_sem = sem_open(to_create, flag, priv, lock);
	if (new_sem == SEM_FAILED)
		__exit__(E_MALLOC, FAILURE, TO_FREE, TO_CLOSE);
	return (new_sem);
}

void	do_sleep(long long ms)
{
	const long long	start = get_time();

	while (get_time() - start < ms
		&& singleton()->die != singleton()->philo_nbr)
		usleep(__MICRO_SEC__);
}

void	print_states(long long start, int index, int s_index)
{
	const long long	current_time = get_time();
	const char		*states[] = {"is eating", "has taken a fork",
		"is sleeping", "is thinking", "died"};

	if (!still_alive())
		return ;
	if (s_index == e_PRINT_DIE)
		sem_wait(singleton()->sem_die);
	sem_wait(singleton()->sem_print);
	printf("[%lld] [%u] [%s]\n", current_time - start, index, states[s_index]);
	sem_post(singleton()->sem_print);
}
