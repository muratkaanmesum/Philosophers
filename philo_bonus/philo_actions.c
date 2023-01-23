/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:03:21 by mmesum            #+#    #+#             */
/*   Updated: 2023/01/23 20:43:48 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
void	eating(t_philo *philo)
{
	sem_wait(philo->data->eat);
	print_message(philo, "is eating");
	philo->last_eat = get_current_time();
	smart_sleep(philo->data->time_to_eat);
	philo->eat_count++;
	sem_post(philo->data->eat);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
}

int	check_if_dead(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philosophers)
	{
		if ((int)(get_current_time()
				- data->philos[i].last_eat) > data->time_to_die)
		{
			data->is_dead = 1;
			return (1);
		}
	}
	return (0);
}

int	check_all_eat(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->number_of_philosophers)
	{
		if (data->philos[i].eat_count < data->must_eat)
			return (0);
	}
	return (1);
}

int	check_all_cases(t_data *data)
{
	if (check_if_dead(data))
		return (1);
	if (check_all_eat(data))
		return (1);
	return (0);
}
