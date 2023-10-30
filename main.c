/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:58:53 by xadabunu          #+#    #+#             */
/*   Updated: 2023/10/30 16:26:10 by xadabunu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	done_eating(t_data *data)
{
	uintmax_t	ts;

	data->all_alive = false;
	pthread_mutex_lock(&(data->print_mutex));
	ts = get_timestamp(data->start);
	printf("%ld all philos ate %ld times\n", ts, data->n_eat);
	pthread_mutex_unlock(&(data->print_mutex));
	return (-1);
}

static int	dead_philo(t_data *data, t_philo philo)
{
	data->all_alive = false;
	pthread_mutex_lock(&(data->print_mutex));
	printf("%lu %lu died\n", get_timestamp(data->start), philo.n);
	pthread_mutex_unlock(&(data->print_mutex));
	return (-1);
}

static int	clear(t_data *data, t_fork *forks, t_philo *philos)
{
	size_t	i;

	i = 0;
	if (philos != NULL)
	{
		while (i < data->n_philo)
		{
			pthread_join(philos[i].t, NULL);
			++i;
		}
		i = 0;
	}
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&(philos[i].left_fork->m));
		++i;
	}
	pthread_mutex_destroy(&(data->print_mutex));
	free(forks);
	free(philos);
	return (0);
}

static int	look_for_death(t_data *data, t_philo *philos)
{
	size_t	i;

	while (data->all_alive)
	{
		i = 0;
		while (i < data->n_philo)
		{
			if (data->tt_die <= get_timestamp(philos[i].last_meal))
				return (dead_philo(data, philos[i]));
			++i;
		}
		if (data->n_philo == data->done_eating)
			return (done_eating(data));
	}
	return (-1);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_fork	*forks;
	t_philo	*philos;

	if (check_args(argc, argv, &data) == -1)
		return (1);
	forks = init_forks(&data);
	if (!forks)
		return (1);
	philos = setup_philos(&data, forks);
	if (!philos)
		return (clear(&data, forks, NULL));
	if (create_threads(&data, philos) == -1)
		return (clear(&data, forks, philos));
	look_for_death(&data, philos);
	clear(&data, forks, philos);
	return (0);
}
