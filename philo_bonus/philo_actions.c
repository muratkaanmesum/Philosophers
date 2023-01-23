/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:03:21 by mmesum            #+#    #+#             */
/*   Updated: 2023/01/23 19:39:55 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
void	eating(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_message(philo, "has taken a fork");
	sem_wait(philo->data->forks);
	print_message(philo, "has taken a fork");
	philo->last_eat = get_current_time();
	sem_wait(philo->data->eat);
	philo->eat_count++;
	sem_post(philo->data->eat);
	print_message(philo, "is eating");
	smart_sleep(philo->data->time_to_eat);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

int	check_if_dead(t_data *data)
{
	int	i;

	sem_wait(data->dead);
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
	sem_post(data->dead);
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
