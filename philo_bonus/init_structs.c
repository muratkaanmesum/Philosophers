/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_structs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 15:03:50 by mmesum            #+#    #+#             */
/*   Updated: 2023/01/27 15:04:22 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

t_data	*init_data(char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->number_of_philosophers = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		data->must_eat = ft_atoi(argv[5]);
	else
		data->must_eat = -1;
	return (data);
}

void	init_philos(t_data *data)
{
	t_philo	*philos;
	int		i;

	i = 0;
	philos = malloc(sizeof(t_philo) * data->number_of_philosophers);
	while (i < data->number_of_philosophers)
	{
		philos[i].id = i + 1;
		philos[i].data = data;
		philos[i].last_eat = get_current_time();
		philos[i].eat_count = 0;
		i++;
	}
	data->philos = philos;
}

void	init_sem(t_data *data)
{
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/eat");
	data->forks = sem_open("/forks", O_CREAT, 0777,
			data->number_of_philosophers);
	data->print = sem_open("/print", O_CREAT, 0777, 1);
	data->eat = sem_open("/eat", O_CREAT, 0777, 1);
}
