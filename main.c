/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 17:58:53 by xadabunu          #+#    #+#             */
/*   Updated: 2023/07/22 17:58:53 by xadabunu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int argc, char **argv, t_data *s);

int	clear(t_data *data, t_fork *forks, t_philo *philos)
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

int	look_for_death(t_data *data, t_philo *philos)
{
	unsigned int	i;
	uintmax_t	now_ms;

	while (data->all_alive == true)
	{
		i = 0;
		usleep(100);
		while (i < data->n_philo)
		{
			if (data->tt_die < get_timestamp(0) - philos[i].last_meal)
			{
				data->all_alive = false;
				now_ms = get_timestamp(data->start);
				printf("%ld %d died\n", now_ms, philos[i].n);
				break ;
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

	if (check_args(argc, argv, &data) == -1)
		return (1);
	forks = init_forks(&data);
	philos = setup_philos(&data, forks);
	if (create_threads(&data, philos) == -1)
		return (clear(&data, forks, philos));
	while (data.all_alive == true)
	{
		if (look_for_death(&data, philos) == -1)
			break ;
	}
	clear(&data, forks, philos);
	return (0);
}
