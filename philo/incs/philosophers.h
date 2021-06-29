/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 14:20:00 by kaye              #+#    #+#             */
/*   Updated: 2021/06/29 17:25:16 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h> 

/* ASCII CODE */
# define B_BLACK "\033[1;30m"
# define B_RED "\033[1;31m"
# define B_GREEN "\033[1;32m"
# define B_YELLOW "\033[1;33m"
# define B_BLUE "\033[1;34m"
# define B_PURPLE "\033[1;35m"
# define B_CYAN "\033[1;36m"
# define NONE "\033[0m"
# define CLR "\033[2J\033[H"

/* ERROR MESSAGE */
# define ERROR_MSG "usage: \033[1;31m./philo [nbr_of_philo] [time_to_die]\n\
               [time_to_eat] [time_to_sleep]\n\
               \033[1;35m[[nbr_of_time_each_philo_must_eat]]\n\033[0m"

/* RETURN */
# define ERROR 1
# define SUCCESS 0

/* MINI LIB */
int		ft_isdigit(int c);
int		ft_strdigit(const char *s);
size_t	ft_strlen(const char *s);
void	ft_putchar(char c);
void	ft_putstr(char *s);
char	*ft_itoa(int n);
int		ft_atoi(const char *str);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);

/* UTILS */
int		__ret__(char *msg, int ret);

#endif