/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 17:43:41 by xadabunu          #+#    #+#             */
/*   Updated: 2023/09/14 21:49:51 by xadabunu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *arg)
{
	t_philo *ph;
	t_data	*data;

	ph = (t_philo *)arg;
	data = ph->data;
	if (ph->n % 2 == 0) // bitwise ?
	{
		ph_starts_thinking(ph);
		ft_usleep(data->tt_eat / 2, data);
	}
	while (data->all_alive)
	{
		ph_eats(ph);
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
		{
			printf("check\n");
			if (i > 0)
			{
				while(--i > 0)
					pthread_join(ph[i].t, NULL);
				pthread_join(ph[i].t, NULL);
			}
			return (-1);
		}
		++i;
	}
	return (0);
}

t_fork	*init_forks(t_data *data)
{
	unsigned int	i;
	t_fork			*forks;

	forks = malloc(sizeof(*forks) * data->n_philo);
	if (forks != NULL)
	{
		i = 0;
		while (i < data->n_philo)
		{
			pthread_mutex_init(&(forks[i].m), NULL);
			++i;
		}
	}
	return (forks);
}

t_philo	*setup_philos(t_data *data, t_fork *forks)
{
	unsigned int	i;
	t_philo			*philos;

	philos = malloc(sizeof(*philos) * data->n_philo);
	if (philos != NULL)
	{
		i = -1;
		while (++i < data->n_philo)
		{
			philos[i].last_meal = data->start;
			philos[i].data = data;
			philos[i].n_eat = data->n_eat;
			philos[i].n_eaten = 0;
			philos[i].left_fork = forks + i;
			if (i == data->n_philo - 1)
				philos[i].right_fork = forks;
			else
				philos[i].right_fork = forks + i + 1;
			philos[i].n = i + 1;
		}
	}
	return (philos);
}
