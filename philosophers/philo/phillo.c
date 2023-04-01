/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phillo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaaitat <imaaitat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 22:49:36 by imaaitat          #+#    #+#             */
/*   Updated: 2023/03/29 01:42:37 by imaaitat         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_phillo		*phillo;
	pthread_mutex_t	died;

	pthread_mutex_init(&died, NULL);
	if (chek_arg(argc, argv))
		return (1);
	phillo = (t_phillo *)malloc(sizeof(t_phillo) * ft_atoi(argv[1]));
	if (!phillo)
		return (1);
	if (init(argc, argv, phillo, &died))
		return (1);
	free(phillo);
	return (0);
}
