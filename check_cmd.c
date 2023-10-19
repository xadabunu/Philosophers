/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xadabunu <xadabunu@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 23:29:06 by xadabunu          #+#    #+#             */
/*   Updated: 2023/09/13 17:35:09 by xadabunu         ###   ########.fr       */
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

static void	set_argv(t_data *data, char **argv, int argc)
{
	data->n_philo = ft_strtoumax(argv[1]);
	data->tt_die = ft_strtoumax(argv[2]);
	data->tt_eat = ft_strtoumax(argv[3]);
	data->tt_sleep = ft_strtoumax(argv[4]);
	if (argc == 6)
		data->n_eat = ft_strtoumax(argv[5]);
	else
		data->n_eat = 0;
	data->done_eating = 0;
}

static bool	only_numbers(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				return (false);
			++j;
		}
		++i;
	}
	return (true);
}

static int	error_message(void)
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

	if (argc < 5 || argc > 6 || !(only_numbers(argv)))
		return (error_message());
	else if (gettimeofday(&test, NULL) != -1)
	{
		set_argv(s, argv, argc);
		s->all_alive = true;
		s->start = get_timestamp(0);
		if (s->n_philo < 1 || s->tt_die < 1 || s->tt_eat < 1 \
			|| s->tt_sleep < 1 || (s->n_eat < 1 && argc == 6))
			return (error_message());
		pthread_mutex_init(&printf_mutex, NULL);
		s->print_mutex = printf_mutex;
		return (0);
	}
	return (-1);
}
