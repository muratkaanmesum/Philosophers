/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 20:45:54 by mmesum            #+#    #+#             */
/*   Updated: 2023/01/23 21:13:20 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->left_fork);
	print_message(philo, "Has taken a fork");
	pthread_mutex_lock(philo->right_fork);
	print_message(philo, "Has taken a fork");
	pthread_mutex_lock(&philo->data->eat);
	philo->last_eat = get_current_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->eat);
	print_message(philo, "Is eating");
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
		if ((int)(get_passed_time(data->philos[i].last_eat)) >
			data->time_to_die)
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
	i = -1;
	while (++i < data->number_of_philosophers)
	{
		if (data->philos[i].eat_count < data->must_eat)
			return (0);
	}
	data->is_dead = 1;
	return (1);
}

int	check_all_cases(t_data *data)
{
	if (check_if_dead(data) == 1 || check_all_eat(data) == 1)
		return (1);
	return (0);
}
