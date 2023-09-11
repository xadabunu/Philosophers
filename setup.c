/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:43:41 by xadabunu          #+#    #+#             */
/*   Updated: 2023/09/11 20:47:37 by xadabunu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *arg)
{
	const t_philo *ph = (t_philo *)arg;

	if (ph->n % 2 == 0)
		ph_starts_thinking(ph);
	while (ph->data->all_alive == true)
	{
		ph_takes_fork(ph, LEFT);
		ph_takes_fork(ph, RIGHT);
		ph_eats(ph);
		ph_drops_forks(ph) ;
		ph_sleeps(ph);
		ph_starts_thinking(ph);
	}
	return (NULL);
}

int	create_threads(t_data *data, t_philo *ph)
{
	unsigned int	i;

	i = 0;
	while (i < data->n_philo)
	{
		if (pthread_create(&(ph[i].t), NULL, &routine, ph + i) != 0)
			return (-1);
		++i;
	}
	return (0);
}

int	init_forks(t_data *data, t_fork **forks)
{
	unsigned int	i;

	*forks = malloc(sizeof(**forks) * data->n_philo);
	if (*forks == NULL)
		return (-1);
	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_init(&((*forks)[i].m), NULL);
		++i;
	}
	return (0);
}

int	setup_philos(t_data *data, t_fork *forks, t_philo **philos)
{
	unsigned int	i;
	t_mutex			print_mutex;

	*philos = malloc(sizeof(**philos) * data->n_philo);
	if (*philos == NULL)
		return (-1);
	pthread_mutex_init(&print_mutex, NULL);
	i = -1;
	while (++i < data->n_philo)
	{
		(*philos)[i].last_meal = data->start;
		(*philos)[i].data = data;
		(*philos)[i].left_fork = forks + i;
		(*philos)[i].print_mutex = &print_mutex;
		if (i == data->n_philo - 1)
			(*philos)[i].right_fork = forks;
		else
			(*philos)[i].right_fork = forks + i + 1;
		(*philos)[i].n = i + 1;
	}
	return (0);
}
