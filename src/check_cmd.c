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

static int	only_numbers(int argc, char **argv)
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

static void	argv_error()
{
	printf("Only positive numbers can be taken as parameters.\n");
}

static void	argc_error()
{
	printf("Usage : ./philo <a> <b> <c> <d> [<e>] with :\n");
	printf("\t a - the number of philosophers/forks at the table.\n");
	printf("\t b - the time (in ms) a philosopher can spend before eating.\n");
	printf("\t c - how long (in ms) it takes a philosopher to eat.\n");
	printf("\t d - how long (in ms) a philosopher sleeps.\n");
	printf("\t e - how many times each philosopher has to eat for the program");
	printf(" to finish.\n");
}

int	check_args(int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		argc_error();
	else if (only_numbers(argc, argv) == 0)
		argv_error();
	else
		return (1);
	return (0);
}