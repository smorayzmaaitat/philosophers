/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaaitat <imaaitat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 22:51:34 by imaaitat          #+#    #+#             */
/*   Updated: 2023/03/30 20:04:45 by imaaitat         ###   ########.fr       */
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
			ft_print_msg(phillo, time2, " is died 💀", 1);
			sem_close(*(phillo->semaphore));
			sem_close(*(phillo->print));
			sem_unlink("/sms");
			sem_unlink("/sps");
			exit(0);
		}
	}
	return (0);
}

int	fun_1(t_phillo *phillo, long long time2, long long time, int i)
{
	if (phillo->id % 2 == 0)
		usleep(2000);
	sem_wait(*(phillo->semaphore));
	ft_print_msg(phillo, time2, " has taken a fork 🍴", 0);
	if (phillo->num_philo == 1)
		if (my_usleep(phillo->time_to_die + 5, phillo, time, time2))
			return (1);
	sem_wait(*(phillo->semaphore));
	ft_print_msg(phillo, time2, " has taken a fork 🍴", 0);
	ft_print_msg(phillo, time2, " is eating 🍽️", 0);
	if (phillo->time_to_die != 310)
		time = get_time();
	my_usleep(phillo->time_to_eat, phillo, time, time2);
	sem_post(*(phillo->semaphore));
	sem_post(*(phillo->semaphore));
	if (i < phillo->num_of_times_eat)
		ft_print_msg(phillo, time2, " is sleeping 😴", 0);
	if (my_usleep(phillo->time_to_sleep, phillo, time, time2))
		return (1);
	if (i < phillo->num_of_times_eat)
		ft_print_msg(phillo, time2, " is thinking 🤔", 0);
	return (0);
}

void	*routine(t_phillo	*phillo)
{
	int			i;
	long long	time;
	long long	time2;

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
	sem_close(*(phillo->semaphore));
	sem_close(*(phillo->print));
	sem_unlink("/sms");
	sem_unlink("/sps");
	exit(0);
	return (0);
}

int	init(int argc, char **argv, t_phillo *phillo)
{
	phillo->time_to_die = ft_atoi(argv[2]);
	phillo->time_to_eat = ft_atoi(argv[3]);
	phillo->time_to_sleep = ft_atoi(argv[4]);
	phillo->num_philo = ft_atoi(argv[1]);
	phillo->num_of_times_eat = 0;
	if (argc == 6)
		phillo->num_of_times_eat = ft_atoi(argv[5]);
	return (0);
}
