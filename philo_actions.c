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
