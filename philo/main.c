/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 23:50:55 by mmesum            #+#    #+#             */
/*   Updated: 2023/01/23 21:32:10 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo(void *data)
{
	t_philo	*philo;

	philo = data;
	if (philo->id % 2 == 0)
		usleep(10000);
	while (philo->data->is_dead == 0)
	{
		eating(philo);
		print_message(philo, "Is sleeping");
		smart_sleep(philo->data->time_to_sleep);
		print_message(philo, "Is thinking");
	}
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
	while (1)
	{
		if (check_all_cases(philos->data) == 1)
			break ;
	}
}

void	finish_all(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->number_of_philosophers)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < philos->data->number_of_philosophers)
	{
		pthread_mutex_destroy(&(philos->data->forks[i]));
		i++;
	}
	free(philos->data->forks);
	free(philos->data);
	free(philos);
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
	data = init_data(argc, argv);
	if (data->number_of_philosophers == 1)
	{
		printf("0 1 philo is dead");
		return (0);
	}
	if (data == NULL)
		return (1);
	philos = init_philos(data);
	init_mutexes(data);
	data->start_time = get_current_time();
	create_threads(philos);
	finish_all(philos);
	return (0);
}
