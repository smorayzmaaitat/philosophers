/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phillo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaaitat <imaaitat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 22:49:36 by imaaitat          #+#    #+#             */
/*   Updated: 2023/03/30 20:04:22 by imaaitat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phillo.h"

int	chek_arg(int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc < 5 || argc > 6)
	{
		printf("%sinvalide arg ⛔!!%s", G_CYAN, RESET);
		return (1);
	}
	while (i < argc)
	{
		if (ft_atoi(argv[i]) <= 0 || ft_atoi(argv[i]) > 2147483647)
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	init_fork(int num, int *n, t_phillo *phillo)
{
	int	i;
	int	pid;

	i = 0;
	while (i < num)
	{
		pid = fork();
		if (pid == 0)
		{
			phillo->id = i + 1;
			routine(phillo);
			exit(0);
		}
		n[i] = pid;
		i++;
	}
}

void	kill_fork(int num, int *n)
{
	int	i;

	i = 0;
	while (i < num)
	{
		kill(n[i], SIGINT);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_phillo	phillo;
	sem_t		*semaphore;
	sem_t		*print;
	int			pid;
	int			*pid_a;

	pid_a = (int *)malloc(sizeof(int) * ft_atoi(argv[1]));
	if (!pid_a)
		return (1);
	semaphore = sem_open("/sms", O_CREAT | O_EXCL, 0644,
			ft_atoi(argv[1]));
	print = sem_open("/sps", O_CREAT | O_EXCL, 0644, 1);
	if (chek_arg(argc, argv))
		return (1);
	if (init(argc, argv, &phillo))
		return (1);
	phillo.semaphore = &semaphore;
	phillo.print = &print;
	init_fork(ft_atoi(argv[1]), pid_a, &phillo);
	pid = waitpid(-1, NULL, 0);
	if (pid != -1 && phillo.num_of_times_eat == 0)
		kill_fork(ft_atoi(argv[1]), pid_a);
	sem_close(semaphore);
	sem_close(print);
	return (free(pid_a), 0);
}
