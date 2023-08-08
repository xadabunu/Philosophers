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

# define ONE_SECOND 1000000

typedef struct s_philo
{
    struct timeval	start;
    unsigned int	n_philo;
    unsigned int	tt_die;
    unsigned int	tt_eat;
    unsigned int	tt_sleep;
    unsigned int	n_eat;
}   t_philo;

typedef struct s_forks
{
    int left;
    int right;
}	t_forks;

int	ft_atoi(const char *str);

#endif