/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaye <kaye@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 14:20:00 by kaye              #+#    #+#             */
/*   Updated: 2021/07/03 19:05:36 by kaye             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
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
# define ERROR_MSG "usage: \033[1;31m./philo [nbr_of_philo : >=2] [time_to_die]\n\
               [time_to_eat] [time_to_sleep]\n\
               \033[1;35m[[nbr_of_time_each_philo_must_eat]]\033[0m"
# define EAT "is eating"
# define FORK "has taken a fork"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define DIE "died"

/* RETURN */
# define FAILURE 1
# define SUCCESS 0
# define TO_FREE 1
# define NOTHING 0

/* FORK STATUS */
# define FORK_IS_DROP 1
# define FORK_IS_TAKE 0

/* AGRS INDEX */
enum    e_args_index
{
    e_NP = 1,
    e_T2D = 2,
    e_T2E = 3,
    e_T2S = 4,
    e_ME = 5
};

/* TIME2 */
enum    e_philo_status
{
    e_DIE,
    e_EAT,
    e_SLEEP,
    e_EATEN,
    e_TAB_NBR
};

/* STRUCT */
typedef struct s_philosophers
{
    pthread_t       philo;
    unsigned int    n_philo;
    unsigned int    nbr_eat; // fiveth opt
}   t_philosophers;

typedef struct s_philo
{
    unsigned int    philo_nbr;
    unsigned int    time2[e_TAB_NBR];
    unsigned int    must_eat;
    t_philosophers  *philo;
    pthread_mutex_t *fork;
    pthread_mutex_t mutex_common;
}   t_philo;

/* PHILOSOPHERS */
void	    *philo(void *args);

/* MINI LIB */
int		    ft_isdigit(int c);
int		    ft_strdigit(const char *s);
int		    ft_atoi(const char *str);
void	    *ft_calloc(size_t count, size_t size);

/* UTILS */
int		    __ret__(char *msg, int ret, int to_free);
t_philo	    *singleton(void);
void	    init_value(void);
void	    get_value(int ac, char **av);
void	    do_sleep(long long ms);
long long	get_time(void);
void	    print_states(long long start, int index, char *status);

//to delete after
void	    print_value(void);
#endif