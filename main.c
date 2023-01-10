#include "Philosophers.h"
void	test(t_data *data)
{
	for (int i = 0; i < 10000000; i++)
		;
}
void	*func(void *data)
{
	printf("ASD\n");
	test();
	printf("%d", ((t_data *)data)->number_of_philosophers);
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
		pthread_create(&thread[i], NULL, func, data);
		i++;
	}
}
int	main(int argc, char *argv[])
{
	pthread_t		*thread;
	t_data			*data;
	pthread_mutex_t	mutex;

	if (argc < 4 || argc != 5)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	pthread_mutex_init(&mutex, NULL);
	data = get_data(argv);
	thread = malloc(sizeof(pthread_t) * data->number_of_philosophers);
	create_threads(thread, data);
	pthread_join(thread, NULL);
	return (0);
}
