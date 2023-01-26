/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 00:21:56 by mmesum            #+#    #+#             */
/*   Updated: 2023/01/26 08:42:33 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				must_eat;
	struct s_philo	*philos;
	unsigned long	start_time;
	pthread_mutex_t	print;
	pthread_mutex_t	eat;
	pthread_mutex_t	dead;
	int				is_dead;
	pthread_mutex_t	*forks;
}					t_data;

typedef struct s_philo
{
	int				id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	int				eat_count;
	unsigned long	last_eat;
	t_data			*data;
	pthread_t		thread;
}					t_philo;

int					ft_atoi(char *str);
t_philo				*init_philos(t_data *data);
int					check_data(int argc, char **argv);
t_data				*init_data(int argc, char **argv);
void				init_mutexes(t_data *data);
unsigned long		get_current_time(void);
unsigned long		get_passed_time(unsigned long begin);
void				print_message(t_philo *philo, char *message);
void				smart_sleep(int time, t_data *data);
void				eating(t_philo *philo);
int					check_all_cases(t_data *data);
int					check_all_eat(t_data *data);
int					check_if_dead(t_data *data);
int					is_dead(t_data *data);
void				assign_dead_value(t_data *data);
#endif
