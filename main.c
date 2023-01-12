/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmesum <mmesum@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 23:50:55 by mmesum            #+#    #+#             */
/*   Updated: 2023/01/13 00:42:26 by mmesum           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Philosophers.h"
t_philo	*get_philo()
{
	t_philo		*philo;
	static int	i;

	philo = malloc(sizeof(t_philo));
	philo->id = i++;
	philo->left_fork = 0;
	philo->right_fork = 0;
	philo->is_eating = 0;
	philo->eat_count = 0;
	philo->last_eat = 0;
	pthread_mutex_init(philo->forks, NULL);
	pthread_mutex_init(philo->print, NULL);
	pthread_mutex_init(philo->death, NULL);
	return (philo);
}
void	*philo(void *data)
{
	t_data	*s_data;
	t_philo	*philo;

	s_data = (t_data *)data;
	pthread_mutex_lock(&s_data->mutex);
	philo = get_philo();
	pthread_mutex_unlock(&s_data->mutex);
	if (s_data->number_of_philosophers % 2 == 0)
		even_philo();
	else
		odd_philo();
	return (NULL);
}
t_data	*get_data(char **argv)
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

void	create_threads(pthread_t *thread, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		pthread_create(&thread[i], NULL, philo, data);
		i++;
	}
}
int	main(int argc, char *argv[])
{
	pthread_t	*thread;
	t_data		*data;
	int			i;

	if (argc < 4 || argc != 5)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	data = get_data(argv);
	pthread_mutex_init(&data->mutex, NULL);
	thread = malloc(sizeof(pthread_t) * data->number_of_philosophers);
	create_threads(thread, data);
	i = -1;
	while (++i < data->number_of_philosophers)
		pthread_join(thread[i], NULL);
	return (0);
}
