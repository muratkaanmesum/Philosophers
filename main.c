/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 23:50:55 by mmesum            #+#    #+#             */
/*   Updated: 2023/01/17 07:12:27 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	*philo(void *data)
{
	t_philo	*philo;

	philo = data;
	if (philo->id % 2 == 0)
		usleep(10000);
	return (NULL);
}

void	create_threads(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->number_of_philosophers)
	{
		pthread_create(&(philos[i].thread), NULL, philo, &philos[i]);
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
	create_threads(philos);
	data->current_time = get_current_time();
	for (int i = 0; i < data->number_of_philosophers; i++)
		pthread_join(philos[i].thread, NULL);
	printf("%dms", get_passed_time(data->current_time));
	return (0);
}
