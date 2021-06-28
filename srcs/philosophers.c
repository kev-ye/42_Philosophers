/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 14:25:25 by kaye              #+#    #+#             */
/*   Updated: 2021/06/28 19:47:07 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int args_check(char **av)
{
	int i;

	i = 1;
	while (av[i])
	{
		if (!ft_strdigit(av[i++]))
			return (ERROR);
	}
	return (SUCCESS);
}

int main(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (__ret__(B_RED"Nbr of args is not a valid !\n"NONE, ERROR));
	if (ac == 5)
	{
		if (ERROR == args_check(av))
			return (__ret__(B_RED"Not a valid args!\n"NONE, ERROR));
	}
	else
	{
		if (ERROR == args_check(av))
			return (__ret__(B_RED"Not a valid args!\n"NONE, ERROR));
	}
	return (SUCCESS);
}