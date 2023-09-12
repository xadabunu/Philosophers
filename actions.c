/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:43:55 by xadabunu          #+#    #+#             */
/*   Updated: 2023/09/12 23:20:24 by xadabunu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_sleeps(const t_philo *philo)
{
	philo_print(philo, SLEEP);
	return (ft_usleep(philo->data->tt_sleep, philo->data));
}

int	ph_takes_fork(const t_philo *philo, int hand)
{
	if (hand == LEFT)
		pthread_mutex_lock(&(philo->left_fork->m));
	else
		pthread_mutex_lock(&(philo->right_fork->m));
	philo_print(philo, FORK);
	return (0);
}

int	ph_eats(t_philo *philo)
{
	pthread_mutex_lock(&(philo->left_fork->m));
	philo_print(philo, FORK);
	pthread_mutex_lock(&(philo->right_fork->m));
	philo_print(philo, FORK);
	philo->last_meal = get_timestamp(0);
	philo_print(philo, EAT);
	ft_usleep(philo->data->tt_eat, philo->data);
	pthread_mutex_unlock(&(philo->left_fork->m));
	pthread_mutex_unlock(&(philo->right_fork->m));
	return (0);
}

int	ph_starts_thinking(const t_philo *philo)
{
	philo_print(philo, THINK);
	return (0);
}
