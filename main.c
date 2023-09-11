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

/*
	un thread en plus || dans le main :
		check toutes les 10us si now - last_meal >= tt_death
		  -> affiche la mort du philo et set all_alive pour tous à 0
		  										=> sortie de boucle
	gérer le retour de la routine -> si all_alive == 1 => an error occured
									 else => somebody died
*/

int	clear(t_data *data, t_fork *forks, t_philo *philos)
{
	size_t	i;

	i = 0;
	pthread_mutex_destroy(philos[0].print_mutex);
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&(philos[i].left_fork->m));
		if (philos != NULL)
			pthread_join(philos[i].t, NULL);
		printf("done\n");
		++i;
	}
	free(forks);
	free(philos);
	return (0);
}

int	look_for_death(t_data *data, t_philo *philos)
{
	unsigned int	i;
	t_time			now;
	unsigned long	now_ms;
	unsigned long	last_meal_ms;

	while (data->all_alive == true)
	{
		i = 0;
		while (i < data->n_philo)
		{
			gettimeofday(&now, NULL);
			now_ms = get_timestamp(&now);
			last_meal_ms = get_timestamp(&(philos[i].last_meal));
			if ((unsigned long)data->tt_die < (now_ms - last_meal_ms))
			{
				printf("%ld %d died\n", now_ms, philos[i].n);
				data->all_alive = false;
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
	if (init_forks(&data, &forks) == -1)
		return (clear(&data, forks, NULL));
	if (setup_philos(&data, forks, &philos) == -1)
		return (clear(&data, forks, philos));
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
