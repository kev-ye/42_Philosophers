/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:05:48 by kaye              #+#    #+#             */
/*   Updated: 2021/07/06 20:06:59 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	_wstatus(int status)
{
	return (status & 0177);
}

int	_wifexited(int status)
{
	return (_wstatus(status) == 0);
}

#if __DARWIN_UNIX03
int	_wexitstatus(int status)
{
	return ((status >> 8) & 0x000000ff);
}
#else

int	_wexitstatus(int status)
{
	return (status >> 8);
}
#endif