/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:43:55 by xadabunu          #+#    #+#             */
/*   Updated: 2023/09/11 20:46:04 by xadabunu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ph_sleeps(const t_philo *philo)
{
	long	timestamp;

	timestamp = get_timestamp(&philo->data->start);
	philo_print(timestamp, philo, SLEEP);
	return (ft_usleep(philo->data->tt_sleep));
}

int	ph_takes_fork(const t_philo *philo, int hand)
{
	long	timestamp;

	if (hand == LEFT)
		pthread_mutex_lock(&(philo->left_fork->m));
	else
		pthread_mutex_lock(&(philo->right_fork->m));
	timestamp = get_timestamp(&philo->data->start);
	philo_print(timestamp, philo, FORK);
	return (0);
}

int	ph_drops_forks(const t_philo *philo)
{
	pthread_mutex_unlock(&(philo->left_fork->m));
	pthread_mutex_unlock(&(philo->right_fork->m));
	return (0);
}

int	ph_eats(const t_philo *philo)
{
	long	timestamp;
	
	timestamp = get_timestamp(&philo->data->start);
	gettimeofday((t_time *)&(philo->last_meal), NULL);
	philo_print(timestamp, philo, EAT);
	return (ft_usleep(philo->data->tt_sleep));
}

int	ph_starts_thinking(const t_philo *philo)
{
	long	timestamp;

	timestamp = get_timestamp(&philo->data->start);
	philo_print(timestamp, philo, THINK);
	return (0);
}
