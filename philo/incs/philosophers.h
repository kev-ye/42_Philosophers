/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 14:20:00 by kaye              #+#    #+#             */
/*   Updated: 2021/06/30 20:04:03 by kaye             ###   ########.fr       */
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

/* MESSAGE */
# define ERROR_MSG "usage: \033[1;31m./philo [nbr_of_philo] [time_to_die]\n\
               [time_to_eat] [time_to_sleep]\n\
               \033[1;35m[[nbr_of_time_each_philo_must_eat]]\n\033[0m"
# define EAT "is eating\n"
# define FORK "has taken a fork\n"
# define SLEEP "is sleeping\n"
# define THINK "is thinking\n"
# define DIE "died"

/* RETURN */
# define ERROR 1
# define SUCCESS 0

/* AGRS INDEX */
# define NBR_PHILO 1
# define T2D 2
# define T2E 3
# define T2S 4
# define MUST_E 5

/* FORK INDEX */
# define L_FORK i
# define R_FORK (i + 1) % singleton()->philo_nbr

/* STATUS */
// # define TAKE_FORK 1
// # define DROP_FORK 0
# define FORK_IS_DROP 1
# define FORK_IS_TAKE 0
# define NO_STATUS 0
# define EATING_STATUS 1
# define SLEEPING_STATUS 2
# define THINKING_STATUS 3

/* STRUCT */
typedef struct s_philosophers
{
    pthread_t       philo;
    unsigned int    n_philo;
    unsigned int    philo_status;
}   t_philosophers;

typedef struct s_fork
{
    unsigned int    n_fork;
    unsigned int    fork_status;
}   t_fork;

typedef struct s_philo
{
    unsigned int    philo_nbr;
    unsigned int    time2die;
    unsigned int    time2eat;
    unsigned int    time2sleep;
    unsigned int    time2think;
    unsigned int    must_eat;
    t_philosophers  *philo;
    t_fork          *fork;
    pthread_mutex_t mutex;
}   t_philo;

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
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t size);

/* PHILOSOPHERS */
long	get_time(void);

/* UTILS */
int		__ret__(char *msg, int ret);
t_philo	*singleton(void);
void	free_all(void);
void	print_value(void); // to delete after

#endif