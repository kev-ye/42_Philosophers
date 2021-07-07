/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 20:07:05 by kaye              #+#    #+#             */
/*   Updated: 2021/07/07 14:36:12 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	_wifsignaled(int status)
{
	return (_wstatus(status) != 0177 && _wstatus(status) != 0);
}

int	_wtermsig(int status)
{
	return (_wstatus(status));
}