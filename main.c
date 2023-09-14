/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:58:53 by xadabunu          #+#    #+#             */
/*   Updated: 2023/09/13 19:57:13 by xadabunu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	dead_philo(t_data *data, t_philo philo)
{
	data->all_alive = false;
	printf("%ld %ld died\n", get_timestamp(data->start), philo.n);
	return (-1);
} 

static int	clear(t_data *data, t_fork *forks, t_philo *philos)
{
	size_t	i;

	if (philos != NULL)
	{
		i = 0;
		while (i < data->n_philo)
		{
			pthread_join(philos[i].t, NULL);
			++i;
		}
		while (i-- > 0)
			pthread_mutex_destroy(&(philos[i].left_fork->m));
	}
	pthread_mutex_destroy(&(data->print_mutex));
	free(forks);
	free(philos);
	return (0);
}

static int	look_for_death(t_data *data, t_philo *philos)
{
	size_t		i;
	uintmax_t	ts;

	while (data->all_alive)
	{
		usleep(100);
		i = 0;
		while (i < data->n_philo)
		{
			ts = get_timestamp(0) - philos[i].last_meal;
			if (data->tt_die < ts)
				return (dead_philo(data, philos[i]));
			if (data->n_philo == data->done_eating)
			{
				data->all_alive = false;
				return (-1);
			}
			++i;
		}
	}
	return (-1);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_fork	*forks;
	t_philo	*philos;
/* is sleeping affiché après que dernier philo ait mangé + timing print death ? */
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
