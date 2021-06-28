/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_lib3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 19:28:31 by kaye              #+#    #+#             */
/*   Updated: 2021/06/28 19:46:08 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_isdigit(int c)
{
	return (c >= 48 && c <= 57);
}

int ft_strdigit(const char *s)
{
    int i;

    i = 0;
    if (!s)
        return (0);
    while (s[i])
    {
        if (!ft_isdigit(s[i++]))
            return (0);
    }
    return (1);
}