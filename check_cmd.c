/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 23:29:06 by xadabunu          #+#    #+#             */
/*   Updated: 2023/07/24 23:29:06 by xadabunu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isspace(const char c);

static uintmax_t	ft_strtoumax(const char *str)
{
	uintmax_t	result;
	uintmax_t	tmp;
	size_t		i;

	result = 0;
	i = 0;
	while (str[i] != '\0')
	{
		tmp = result;
		result = 10 * result + (uintmax_t)str[i] - '0';
		if (result < tmp)
			return (0);
		++i;
	}
	return (result);
}

static int	ft_isnbr(char *str)
{
	int	i;

	i = 0;
	while (ft_isspace(str[i]))
		++i;
	while (str[i] != '\0')
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		++i;
	}
	return (1);
}

static int	only_numbers(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_isnbr(argv[i]) == 0)
			return (0);
		++i;
	}
	return (1);
}

static int	error_message()
{
	printf("Usage : \"./philo <A> <B> <C> <D> [<E>]\" with :\n");
	printf("\t A - the number of philosophers around the table.\n");
	printf("\t B - the time (in ms) a philosopher can spend before eating.\n");
	printf("\t C - how long (in ms) it takes a philosopher to eat.\n");
	printf("\t D - how long (in ms) a philosopher sleeps.\n");
	printf("\t E - how many times each philosopher has to eat for the ");
	printf("simulation to stop without any philosopher dying (optionnal).\n");
    printf("All these numbers must be stricly positive integers.\n");
	return (-1);
}

int	check_args(int argc, char **argv, t_data *s)
{
	t_mutex	printf_mutex;
	t_time	test;

	if (argc < 5 || argc > 6 || only_numbers(argv) == 0)
		return (error_message());
	else if (gettimeofday(&test, NULL) != -1)
	{
		s->n_philo = ft_strtoumax(argv[1]);
		s->tt_die = ft_strtoumax(argv[2]) * 1;
		s->tt_eat = ft_strtoumax(argv[3]) * 1;
		s->tt_sleep = ft_strtoumax(argv[4]) * 1;
		s->all_alive = true;
		s->start = get_timestamp(0);
		if (argc == 6)
			s->n_eat = ft_strtoumax(argv[5]);
		else
			s->n_eat = 0;
		if (s->n_philo < 1 || s->tt_die < 1 || s->tt_eat < 1 \
			|| s->tt_sleep < 1 || (s->n_eat < 1 && argc == 6))
			return (error_message());
		pthread_mutex_init(&printf_mutex, NULL);
		s->print_mutex = printf_mutex;
		return (0);
	}
	return (-1);
}
