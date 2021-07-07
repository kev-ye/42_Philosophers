/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:14:40 by kaye              #+#    #+#             */
/*   Updated: 2021/07/06 20:20:53 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	__free__(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

void    __mutex_unlock__(void)
{
    int i;

    i = 0;
    while (i < singleton()->philo_nbr)
    {
        sem_close(singleton()->fork[i].fork);
		if (singleton()->fork[i].sem_name)
		{
        	sem_unlink(singleton()->fork[i].sem_name);
        	_free__(singleton()->fork[i].sem_name);
		}
        ++i;
    }
    __free__(singleton()->fork);
    sem_close(singleton()->sem_common);
    sem_unlink("common");
}

int	__exit__(char *msg, int ret, int to_free, int to_close)
{
	int i;

	if (msg)
		printf("%s\n", msg);
	if (TO_FREE == to_free)
	{
		if (singleton())
		{
            if (TO_CLOSE == to_close)
                __mutex_unlock__();
			if (singleton()->philo)
				__free__(singleton()->philo);
			if (singleton()->philo)
				__free__(singleton()->fork);
		}
		__free__(singleton());
	}
	exit(ret);
}