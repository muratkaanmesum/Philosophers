/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 00:21:56 by mmesum            #+#    #+#             */
/*   Updated: 2023/01/23 19:01:14 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
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
	sem_t			*dead;
}					t_data;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	unsigned long	last_eat;
	t_data			*data;
	pid_t			pid;
}					t_philo;
# define DEBUG printf("DEBUG: %s:%d:%s(): ", __FILE__, __LINE__, __func__);
int					ft_atoi(char *str);
t_philo				*init_philos(t_data *data);
t_data				*init_data(char **argv);
void				init_mutexes(t_data *data);
unsigned long		get_current_time(void);
unsigned long		get_passed_time(unsigned long begin);
void				print_message(t_philo *philo, char *message);
void				smart_sleep(int time);
int					check_all_cases(t_data *data);
void				eating(t_philo *philo);
void				init_sem(t_data *data);
#endif
