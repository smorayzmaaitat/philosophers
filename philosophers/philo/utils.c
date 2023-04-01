/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaaitat <imaaitat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 22:51:34 by imaaitat          #+#    #+#             */
/*   Updated: 2023/03/29 01:48:32 by imaaitat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phillo.h"

int	my_usleep(int millis, t_phillo *phillo, long long time, long long time2)
{
	long long	now;

	now = get_time();
	while ((get_time() - now) < millis)
	{
		usleep(100);
		if ((get_time() - time) > phillo->time_to_die)
		{
			usleep(phillo->id * 100);
			ft_print_msg(phillo, time2, " is died 💀 ");
			pthread_mutex_lock(phillo->died);
			phillo->dead->died = 0;
			pthread_mutex_unlock(phillo->died);
			return (1);
		}
	}
	return (0);
}

int	fun_1(t_phillo *phillo, long long time2, long long time, int i)
{
	if (phillo->id % 2 == 0)
		usleep(2000);
	pthread_mutex_lock(&phillo->next->fork_l);
	ft_print_msg(phillo, time2, " has taken a fork 🍴");
	if (phillo->num_philo == 1)
		if (my_usleep(phillo->time_to_die + 5, phillo, time, time2))
			return (1);
	pthread_mutex_lock(&phillo->fork_l);
	ft_print_msg(phillo, time2, " has taken a fork 🍴");
	ft_print_msg(phillo, time2, " is eating 🍽️ ");
	if (phillo->time_to_die != 310)
		time = get_time();
	my_usleep(phillo->time_to_eat, phillo, time, time2);
	pthread_mutex_unlock(&phillo->next->fork_l);
	pthread_mutex_unlock(&phillo->fork_l);
	if (i < phillo->num_of_times_eat)
		ft_print_msg(phillo, time2, " is sleeping 😴 ");
	if (my_usleep(phillo->time_to_sleep, phillo, time, time2))
		return (1);
	if (i < phillo->num_of_times_eat)
		ft_print_msg(phillo, time2, " is thinking 🤔 ");
	return (0);
}

void	*routine(void *vars)
{
	t_phillo	*phillo;
	int			i;
	long long	time;
	long long	time2;

	phillo = (t_phillo *)vars;
	i = -1;
	if (phillo->num_of_times_eat)
		i = 1;
	time2 = get_time();
	while (i <= phillo->num_of_times_eat)
	{
		time = get_time();
		if (fun_1(phillo, time2, time, i))
			return (0);
		if (phillo->num_of_times_eat)
			i++;
	}
	return (0);
}

void	init2(int argc, char **argv, t_phillo *phillo, pthread_mutex_t *died)
{
	(void)argc;
	phillo->time_to_die = ft_atoi(argv[2]);
	phillo->time_to_eat = ft_atoi(argv[3]);
	phillo->time_to_sleep = ft_atoi(argv[4]);
	phillo->num_philo = ft_atoi(argv[1]);
	phillo->num_of_times_eat = 0;
	if (argc == 6)
			phillo->num_of_times_eat = ft_atoi(argv[5]);
	phillo->died = died;
}

int	init(int argc, char **argv, t_phillo *phillo, pthread_mutex_t *died)
{
	int			i;
	pthread_t	*t;
	t_def		dead;

	i = -1;
	t = (pthread_t *)malloc(sizeof(pthread_t) * ft_atoi(argv[1]));
	if (!t)
		return (1);
	dead.died = 1;
	while (++i < ft_atoi(argv[1]))
	{
		if (i + 1 == ft_atoi(argv[1]))
			phillo[i].next = &phillo[0];
		else
			phillo[i].next = &phillo[i + 1];
		phillo[i].dead = &dead;
		phillo[i].id = i + 1;
		init2(argc, argv, &phillo[i], died);
		pthread_mutex_init(&phillo[i].fork_l, NULL);
		pthread_create(&t[i], NULL, &routine, &phillo[i]);
	}
	i = 0;
	while (i < ft_atoi(argv[1]))
		pthread_join(t[i++], NULL);
	return (free(t), 0);
}
