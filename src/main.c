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

#include "../include/philo.h"

int	check_args(int argc, char **argv, t_philo *s);

void	*routine(void *arg)
{
	struct timeval t;
	struct timeval u;
	t_philo *s;

	s = (t_philo *)arg;
	gettimeofday(&u, NULL);
	usleep(s->time_death * 1000);
	gettimeofday(&t, NULL);
	printf("time_death : %ld\n", t.tv_usec - u.tv_usec);
	return (NULL);
}

int	create_threads(t_philo *s)
{
	int	i;
	pthread_t t;

	i = 0;
	printf("-> %f\n", s->time_death);
	while (i < s->n_philo)
	{
		pthread_create(&t, NULL, &routine, s);
	}
	(void)s;
	return (0);
}

int	main(int argc, char **argv)
{
	t_philo	s;
	//pthread_t t;

	if (check_args(argc, argv, &s) == 0)
		return (1);


	struct timeval time;
	struct timeval u;
	gettimeofday(&u, NULL);
	usleep(s.time_death * 1000);
	gettimeofday(&time, NULL);

	printf("time_death : %ld\n", time.tv_sec - u.tv_sec);
	
	// if (create_threads(&s) == -1)
	// 	return (2);
	//pthread_create(&t, NULL, &routine, &s);
	//pthread_join(t, NULL);
	/*
	** algo;
	*/
	return (0);
}