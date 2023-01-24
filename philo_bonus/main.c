/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 23:50:55 by mmesum            #+#    #+#             */
/*   Updated: 2023/01/24 14:08:45 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*is_dead(void *input)
{
	t_philo	*philo;

	philo = input;
	while (1)
	{
		sem_wait(philo->data->eat);
		if (get_passed_time(philo->last_eat) > (unsigned long)philo->data->time_to_die)
		{
			print_message(philo, "is dead");
			philo->data->is_dead = 1;
			exit(1);
		}
		sem_post(philo->data->eat);
		usleep(1000);
		if (philo->data->is_dead)
			break ;
	}
	return (NULL);
}

void	philo(t_philo *philo)
{
	pthread_create(&philo->dead_thread, NULL, &is_dead, philo);
	pthread_detach(philo->dead_thread);
	if (philo->id % 2 == 0)
		usleep(10000);
	while (philo->data->is_dead == 0)
	{
		eating(philo);
		if (philo->eat_count >= philo->data->must_eat
			&& philo->data->must_eat != -1)
			break ;
		print_message(philo, "is sleeping");
		smart_sleep(philo->data->time_to_sleep, philo->data);
		print_message(philo, "is thinking");
	}
	pthread_join(philo->dead_thread, NULL);
	if (philo->data->is_dead)
		exit(1);
	exit(0);
}

void	create_processes(t_data *data)
{
	pid_t	pid;
	int		i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pid = fork();
		if (pid < 0)
		{
			printf("Error: fork failed");
		}
		else if (pid == 0)
		{
			data->philos[i].pid = pid;
			philo(&data->philos[i]);
		}
		i++;
		usleep(100);
	}
}

void	close_processes(t_data *data)
{
	int	i;
	int	ret;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		waitpid(-1, &ret, 0);
		if (ret != 0)
		{
			i = -1;
			while (++i < data->number_of_philosophers)
				kill(data->philos[i].pid, SIGINT);
			break ;
		}
		i++;
	}
	sem_unlink("/forks");
	sem_unlink("/print");
	sem_unlink("/eat");
	sem_close(data->eat);
	sem_close(data->forks);
	sem_close(data->print);
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	if (argc != 5 && argc != 6)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	data = init_data(argv);
	init_philos(data);
	init_sem(data);
	data->start_time = get_current_time();
	create_processes(data);
	close_processes(data);
	return (0);
}
