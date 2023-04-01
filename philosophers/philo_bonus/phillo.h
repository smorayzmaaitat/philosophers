/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phillo.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imaaitat <imaaitat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 22:49:59 by imaaitat          #+#    #+#             */
/*   Updated: 2023/03/30 20:37:54 by imaaitat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILLO_H
# define PHILLO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <semaphore.h>
# include <unistd.h>
# include <signal.h>
# define RESET "\e[0m"
# define PINK "\e[0;38;5;199m"
# define GREEN "\e[0;32m"
# define BLUE "\e[0;34m"
# define G_BLUE "\e[0;38;5;24m"
# define B_BLUE "\e[1;34m"
# define G_CYAN "\e[0;38;5;44m"
# define RED "\033[0;31m"

typedef struct phillo
{
	int				id;
	int				chek;
	int				num_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	sem_t			**semaphore;
	sem_t			**print;
	int				num_of_times_eat;
}					t_phillo;

long long			get_time(void);
int					chek_arg(int argc, char **argv);
int					my_usleep(int millis, t_phillo *phillo, long long time,
						long long time2);
int					chek_arg(int argc, char **argv);
void				*routine(t_phillo	*phillo);
int					init(int argc, char **argv, t_phillo *phillo);
void				ft_print_msg(t_phillo *phillo, long long time2,
						char *s, int chek);
long long			get_time(void);
int					ft_atoi(const char *str);
#endif