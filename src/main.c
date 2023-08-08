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
	t_philo *s;

	s = (t_philo *)arg;
	/*
		algo
		wait forks
		take forks
		eat
		drop forks
		sleep
	*/

	return (NULL);
}

/*
	second routine starting with sleep depending on tt_eat == tt_sleep ?
*/

int	create_threads(t_philo *s)
{
	int	i;
	pthread_t t;

	i = 0;
	while (i < s->n_philo)
	{
		pthread_create(&t, NULL, &routine, s);
	}
	(void)s;
	return (0);
}

int	ft_sleep(unsigned int time)
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

int	main(int argc, char **argv)
{
	t_philo	s;
	pthread_t *t;

	if (check_args(argc, argv, &s) == 0)
		return (1);

	t = malloc(sizeof(*t) * s.n_philo);
	pthread_mutex_t	mutex;
	pthread_mutex_init(&mutex, NULL);
	pthread_mutex_lock(&mutex);
	pthread_mutex_unlock(&mutex);
	pthread_mutex_destroy(&mutex);

	// if (create_threads(&s) == -1)
	// 	return (2);
	//pthread_create(&t, NULL, &routine, &s);
	//pthread_join(t, NULL);
	/*
	** algo;
	*/
	return (0);
}