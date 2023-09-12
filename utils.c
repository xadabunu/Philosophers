/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/28 11:36:19 by xadabunu          #+#    #+#             */
/*   Updated: 2023/07/28 11:36:19 by xadabunu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isspace(const char c)
{
	return (c == '\n' || c == '\t' || c == '\v' || c == ' ' || c == '\r' \
	|| c == '\f');
}

int	ft_atoi(const char *str)
{
	unsigned int	i;
	long			res;
	int				sign;
	long			tmp;

	if (!str)
		return (0);
	i = 0;
	while (ft_isspace(str[i]))
		++i;
	sign = 1;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	res = 0;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		tmp = res;
		res = res * 10 + str[i] - '0';
		if (tmp > res)
			return (-1 * (sign == 1));
		++i;
	}
	return (sign * res);
}

size_t	get_timestamp(const uintmax_t start_ms)
{
	t_time			now;
	unsigned long	now_ms;

	gettimeofday(&now, NULL);
	now_ms = now.tv_sec * 1000 + now.tv_usec / 1000;
	return (now_ms - start_ms);
}

int	ft_usleep(uintmax_t tt_sleep, t_data *data)
{
	uintmax_t	start_ms;
	uintmax_t	time_slept;
	t_time		now;

	start_ms =  get_timestamp(0);
	time_slept = 0;
	while(time_slept < tt_sleep)
	{
		if (data->all_alive == false)
			return (-1);
		usleep(100);
		gettimeofday(&now, NULL);
		time_slept = get_timestamp(start_ms);
	}
	return (0);
}

void	philo_print(const t_philo *philo, char *state)
{
	unsigned long	timestamp;
	t_data			*data;

	data = philo->data;
	pthread_mutex_lock(&(data->print_mutex));
	if (data->all_alive)
	{
		timestamp = get_timestamp(data->start);
		printf("%lu %d %s\n", timestamp, philo->n, state);
	}
	pthread_mutex_unlock(&(data->print_mutex));
}
