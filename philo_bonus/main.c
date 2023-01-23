/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 23:50:55 by mmesum            #+#    #+#             */
/*   Updated: 2023/01/23 17:35:45 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
void	philo(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(10000);
	while (philo->data->is_dead != 1)
	{
		eating(philo);
		print_message(philo, "is sleeping");
		smart_sleep(philo->data->time_to_sleep);
		print_message(philo, "is thinking");
	}
}
void	create_processes(t_data *data, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		philo(&data->philos[i]);
}

int	main(int argc, char *argv[])
{
	t_data	*data;
	t_philo	*philos;
	int		i;

	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	data = init_data(argv);
	philos = init_philos(data);
	data->start_time = get_current_time();
	i = 0;
	while (i < data->number_of_philosophers)
	{
		create_processes(data, i);
		i++;
	}
	while (1)
	{
		if (check_all_cases(data) == 1)
			exit(1);
	}
	return (0);
}
