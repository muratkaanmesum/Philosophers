/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 23:50:55 by mmesum            #+#    #+#             */
/*   Updated: 2023/01/20 00:21:58 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"

void	*philo(void *data)
{
	t_philo	*philo;

	philo = data;
	if (philo->id % 2 == 0)
		usleep(10000);
	while (philo->data->is_dead == 0)
	{
		eating(philo);
		pthread_mutex_lock(&philo->data->print);
		print_message(philo, "Is sleeping");
		pthread_mutex_unlock(&philo->data->print);
		smart_sleep(philo->data->time_to_sleep);
		pthread_mutex_lock(&philo->data->print);
		print_message(philo, "Is thinking");
		pthread_mutex_unlock(&philo->data->print);
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
		if (check_all_eat(philos->data))
			break ;
		if (check_if_dead(philos->data))
			break ;
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
	data->start_time = get_current_time();
	create_threads(philos);
	for (int i = 0; i < data->number_of_philosophers; i++)
		pthread_join(philos[i].thread, NULL);
	return (0);
}
