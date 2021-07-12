/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:14:40 by kaye              #+#    #+#             */
/*   Updated: 2021/07/12 20:18:38 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	__free__(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	__sem_unlock__(void)
{
	sem_close(singleton()->sem_fork);
	sem_unlink(S_FORK);
	sem_close(singleton()->sem_kill);
	sem_unlink(S_KILL);
	sem_close(singleton()->sem_die);
	sem_unlink(S_DIE);
	sem_close(singleton()->sem_print);
	sem_unlink(S_PRINT);
	sem_close(singleton()->sem_philo_must_eat_counter);
	sem_unlink(S_PMEC);
}

int	__exit__(char *msg, int ret, int to_free, int to_close)
{
	if (msg)
		printf("%s\n", msg);
	if (TO_FREE == to_free)
	{
		if (singleton())
		{
			if (TO_CLOSE == to_close)
				__sem_unlock__();
			if (singleton()->philo)
				__free__(singleton()->philo);
		}
		__free__(singleton());
	}
	exit(ret);
}
