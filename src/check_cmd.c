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

#include "../include/philo.h"

static int	ft_isnbr(char *str)
{
	int	i;

	i = 0;
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

static void	error_message()
{
	printf("Usage : ./philo <A> <B> C> <D> [<E>] with :\n");
	printf("\t A - the number of philosophers/forks at the table.\n");
	printf("\t B - the time (in ms) a philosopher can spend before eating.\n");
	printf("\t C - how long (in ms) it takes a philosopher to eat.\n");
	printf("\t D - how long (in ms) a philosopher sleeps.\n");
	printf("\t E - how many times each philosopher has to eat for the ");
	printf("simulation to stop without any philosophe dying (optionnal).\n");
    printf("All these numbers must be stricly positive.\n");
}

int	check_args(int argc, char **argv, t_philo *s)
{
	if (argc < 5 || argc > 6 || only_numbers(argv) == 0)
		error_message();
	else
	{
		gettimeofday(&(s->start), NULL);
		s->n_philo = ft_atoi(argv[1]);
		s->tt_die = ft_atoi(argv[2]) * 1000;
		s->tt_eat = ft_atoi(argv[3]) * 1000;
		s->tt_sleep = ft_atoi(argv[4]) * 1000;
		if (argc == 6)
        	s->n_eat = ft_atoi(argv[5]);
		else
			s->n_eat = 0;
		return (1);
    }
	return (0);
}
