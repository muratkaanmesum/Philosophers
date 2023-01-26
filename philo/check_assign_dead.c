#include "philo.h"

void	assign_dead_value(t_data *data)
{
	pthread_mutex_lock(&data->dead);
	data->is_dead = 1;
	pthread_mutex_unlock(&data->dead);
}
int	is_dead(t_data *data)
{
	pthread_mutex_lock(&data->dead);
	if (data->is_dead == 1)
	{
		pthread_mutex_unlock(&data->dead);
		return (1);
	}
	pthread_mutex_unlock(&data->dead);
	return (0);
}
