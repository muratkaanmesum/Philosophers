/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 00:21:56 by mmesum            #+#    #+#             */
/*   Updated: 2023/01/27 15:03:41 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
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
	int				is_dead;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*eat;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	unsigned long	last_eat;
	t_data			*data;
	pthread_t		dead_thread;
	pid_t			pid;
}					t_philo;

int					ft_atoi(char *str);
void				init_philos(t_data *data);
t_data				*init_data(char **argv);
unsigned long		get_current_time(void);
unsigned long		get_passed_time(unsigned long begin);
void				print_message(t_philo *philo, char *message);
void				smart_sleep(int time, t_data *data);
int					check_all_cases(t_data *data);
void				eating(t_philo *philo);
void				init_sem(t_data *data);
int					check_all_eat(t_data *data);
int					check_data(int argc, char **argv);
#endif
