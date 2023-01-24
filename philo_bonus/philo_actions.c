/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 16:03:21 by mmesum            #+#    #+#             */
/*   Updated: 2023/01/24 13:18:49 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	eating(t_philo *philo)
{
	sem_wait(philo->data->forks);
	print_message(philo, "has taken a fork");
	sem_wait(philo->data->forks);
	print_message(philo, "has taken a fork");
	sem_wait(philo->data->eat);
	print_message(philo, "is eating");
	philo->last_eat = get_current_time();
	philo->eat_count++;
	sem_post(philo->data->eat);
	smart_sleep(philo->data->time_to_eat, philo->data);
	sem_post(philo->data->forks);
	sem_post(philo->data->forks);
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
	return (1);
}
