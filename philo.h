/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:59:12 by xadabunu          #+#    #+#             */
/*   Updated: 2023/07/22 17:59:12 by xadabunu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <inttypes.h>
# include <stdbool.h>

# define ONE_SECOND 1000000
# define LEFT 0
# define RIGHT 1

# define EAT	"is eating"
# define FORK	"has taken a fork"
# define SLEEP	"is sleeping"
# define THINK	"starts thinking"
# define DIE	"died"

typedef pthread_mutex_t t_mutex;
typedef struct timeval	t_time;

typedef struct s_data
{
    uintmax_t			start;
    uintmax_t			n_philo;
	uintmax_t			tt_die;
    uintmax_t			tt_eat;
    uintmax_t			tt_sleep;
    _Atomic uintmax_t	n_eat;
    _Atomic bool		all_alive;
	t_mutex				print_mutex;
}   t_data;

typedef struct s_fork
{
	t_mutex	m;
}	t_fork;

typedef struct s_philo
{
	pthread_t	t;
	int			n;
	size_t		last_meal;
	t_data		*data;
	t_fork		*left_fork;
	t_fork		*right_fork;
}	t_philo;

int	ft_atoi(const char *str);
int	ft_usleep(uintmax_t time, t_data *data);
size_t	get_timestamp(const uintmax_t time);
void	philo_print(const t_philo *philo, char *state);

t_philo	*setup_philos(t_data *data, t_fork *forks);
t_fork	*init_forks(t_data *data);
int	create_threads(t_data *data, t_philo *ph);

int	ph_sleeps(const t_philo *philo);
int	ph_takes_fork(const t_philo *philo, int hand);
int	ph_eats(t_philo *philo);
int	ph_starts_thinking(const t_philo *philo);

#endif
