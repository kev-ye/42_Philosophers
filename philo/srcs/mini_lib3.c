/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_lib3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 19:28:31 by kaye              #+#    #+#             */
/*   Updated: 2021/06/30 15:03:57 by kaye             ###   ########.fr       */
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

void	ft_bzero(void *s, size_t n)
{
	while (n)
		((unsigned char *)s)[--n] = 0;
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = (void *)malloc(count * size);
	if (ptr)
		ft_bzero(ptr, count * size);
	return (ptr);
}