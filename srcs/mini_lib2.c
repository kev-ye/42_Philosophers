/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_lib2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 19:24:24 by kaye              #+#    #+#             */
/*   Updated: 2021/06/28 19:25:48 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static size_t	ft_intlen(int n)
{
	size_t	count;

	if (n != 0)
		count = 0;
	else
		count = 1;
	while (n)
	{
		n = n / 10;
		++count;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	size_t			len;
	char			*str;
	unsigned int	n_tmp;

	if (n < 0)
		n_tmp = -(unsigned int)n;
	else
		n_tmp = n;
	if (n < 0)
		len = ft_intlen(n_tmp) + 1;
	else
		len = ft_intlen(n_tmp);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len--)
	{
		str[len] = n_tmp % 10 + '0';
		n_tmp /= 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

int	ft_atoi(const char *str)
{
	int	signe;
	int	res;

	signe = 1;
	res = 0;
	while (*str && ((*str >= '\t' && *str <= '\r') || (*str == ' ')))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			signe = -1;
		++str;
	}
	while (*str && ft_isdigit(*str))
	{
		res = res * 10 + *str - '0';
		++str;
	}
	return (res * signe);
}


int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	i = 0;
	while ((s1[i] || s2[i]) && (s1[i] == s2[i]))
		i++;
	return (s1[i] - s2[i]);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while ((*s1 || *s2) && (*s1 == *s2) && --n)
	{
		++s1;
		++s2;
	}
	if (n)
		return (((unsigned char) *s1) - ((unsigned char) *s2));
	return (0);
}
