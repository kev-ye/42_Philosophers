/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:14:40 by kaye              #+#    #+#             */
/*   Updated: 2021/07/12 14:51:47 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	__free__(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

void    __sem_unlock__(void)
{
	sem_close(singleton()->sem_fork);
	sem_unlink("sem_fork");
    sem_close(singleton()->sem_common);
    sem_unlink("sem_common");
	sem_close(singleton()->sem_kill);
    sem_unlink("sem_kill");
	sem_close(singleton()->sem_die);
    sem_unlink("sem_die");
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