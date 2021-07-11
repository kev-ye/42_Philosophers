/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:14:40 by kaye              #+#    #+#             */
/*   Updated: 2021/07/11 17:54:12 by kaye             ###   ########.fr       */
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
	sem_close(singleton()->fork);
	sem_unlink("fork");
    sem_close(singleton()->sem_common);
    sem_unlink("common");
	sem_close(singleton()->sem_common);
    sem_unlink("kill_philo");
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