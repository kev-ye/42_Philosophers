/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:14:40 by kaye              #+#    #+#             */
/*   Updated: 2021/07/11 14:12:33 by kaye             ###   ########.fr       */
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
	sem_close(singleton()->fork);
	sem_unlink("fork");
    sem_close(singleton()->sem_common);
    sem_unlink("common");
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
                __mutex_unlock__();
			if (singleton()->philo)
				__free__(singleton()->philo);
		}
		__free__(singleton());
	}
	exit(ret);
}