/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 00:21:56 by mmesum            #+#    #+#             */
/*   Updated: 2023/01/16 19:39:31 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				must_eat;
	struct s_philo	*philos;
}					t_data;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	right_fork;
	int				eat_count;
	int				last_eat;
	int				*is_eating;
	t_data			*data;
	pthread_t		thread;
	pthread_mutex_t	*print;
	pthread_mutex_t	*death;
}					t_philo;

int					ft_atoi(char *str);
t_philo				*init_philos(t_data *data);
t_data				*init_data(char **argv);
void				init_mutexes(t_data *data);
#endif
