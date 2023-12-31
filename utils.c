/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 11:36:19 by xadabunu          #+#    #+#             */
/*   Updated: 2023/10/26 21:15:38 by xadabunu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isspace(const char c)
{
	return (c == '\n' || c == '\t' || c == '\v' || c == ' ' || c == '\r' \
	|| c == '\f');
}

uintmax_t	get_timestamp(const uintmax_t start_ms)
{
	t_time		now;
	uintmax_t	now_ms;

	gettimeofday(&now, NULL);
	now_ms = now.tv_sec * 1000 + now.tv_usec / 1000;
	return (now_ms - start_ms);
}

int	ft_usleep(uintmax_t tt_sleep, t_data *data)
{
	uintmax_t	start_ms;
	uintmax_t	time_slept;
	t_time		now;

	start_ms = get_timestamp(0);
	time_slept = 0;
	while (time_slept < tt_sleep)
	{
		if (!(data->all_alive))
			return (-1);
		usleep(2 * data->n_philo);
		gettimeofday(&now, NULL);
		time_slept = get_timestamp(start_ms);
	}
	return (0);
}

void	philo_print(const t_philo *philo, char *state)
{
	t_data			*data;

	data = philo->data;
	pthread_mutex_lock(&(data->print_mutex));
	if (data->all_alive)
		printf("%lu %lu %s\n", get_timestamp(data->start), philo->n, state);
	pthread_mutex_unlock(&(data->print_mutex));
}
