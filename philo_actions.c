#include "Philosophers.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_message(philo, "Has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_message(philo, "Has taken a fork");
	philo->last_eat = get_current_time();
	print_message(philo, "Is eating");
	philo->eat_count++;
	smart_sleep(philo->data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

int	check_if_dead(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philosophers)
	{
		if (get_passed_time(data->philos[i].last_eat) > (unsigned long)data->time_to_die)
		{
			print_message(&data->philos[i], "Is dead");
			data->is_dead = 1;
			return (1);
		}
	}
	return (0);
}

int	check_all_eat(t_data *data)
{
	int	i;

	if (data->must_eat == -1)
		return (0);
	i = 0;
	while (i < data->number_of_philosophers
		&& data->philos[i].eat_count >= data->must_eat)
		i++;
	if (i == data->number_of_philosophers)
	{
		data->is_dead = 1;
		return (1);
	}
	return (0);
}

int	check_all_cases(t_data *data)
{
	if (check_if_dead(data) == 1 || check_all_eat(data) == 1)
		return (1);
	return (0);
}
