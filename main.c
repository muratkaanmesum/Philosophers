/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 23:50:55 by mmesum            #+#    #+#             */
/*   Updated: 2023/01/16 19:38:23 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	*philo(void *data)
{
	(void)data;
	return (NULL);
}

void	create_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_create(&(data->philos[i].thread), NULL, philo, data);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_data	*data;
	t_philo	*philos;

	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	data = init_data(argv);
	philos = init_philos(data);
	init_mutexes(data);
	return (0);
}
