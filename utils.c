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

long	get_timestamp(t_time *start)
{
	t_time			now;
	unsigned long	now_ms;
	unsigned long	start_ms;

	if (gettimeofday(&now, NULL) == -1)
		return (-1);
	now_ms = now.tv_sec * 1000 + now.tv_usec / 1000;
	start_ms = start->tv_sec * 1000 + start->tv_usec / 1000;
	return (now_ms - start_ms);
}

int	ft_usleep(unsigned int time)
{
	while (time > ONE_SECOND)
	{
		if (usleep(ONE_SECOND) == -1)
			return (-1);
		time -= ONE_SECOND;
	}
	if (usleep(time) == -1)
		return (-1);
	return (0);
}

void	philo_print(unsigned long timestamp, const t_philo *philo, char *state)
{
	pthread_mutex_lock(philo->print_mutex);
	printf("%lu %d %s\n", timestamp, philo->n, state);
	pthread_mutex_unlock(philo->print_mutex);
}
