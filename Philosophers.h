#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_data
{
	int				number_of_philosophers;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				must_eat;
	pthread_mutex_t	mutex;
}					t_data;

typedef struct s_all
{
	t_data			*data;
}					t_all;

//add protection
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

int					ft_atoi(char *str);
void				*func(void *data);
#endif
