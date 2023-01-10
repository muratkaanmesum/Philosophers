#include "Philosophers.h"
void	test(t_all *all)
{
	printf("inside %d\n", all->data->number_of_philosophers);
	pthread_mutex_lock(&all->data->mutex);
	for (int i = 0; i < 1000000; i++)
		;
	printf("Finished\n");
	pthread_mutex_unlock(&all->data->mutex);
}
void	*func(void *all)
{
	test(all);
	printf("%d\n", ((t_all *)all)->data->number_of_philosophers);
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
void	create_threads(pthread_t *thread, t_all *all)
{
	int	i;

	i = 0;
	while (i < all->data->number_of_philosophers)
	{
		pthread_create(&thread[i], NULL, func, all);
		i++;
	}
}
int	main(int argc, char *argv[])
{
	pthread_t		*thread;
	t_all			*all;
	pthread_mutex_t	mutex;

	if (argc < 4 || argc != 5)
	{
		printf("Error: wrong number of arguments\n");
		return (1);
	}
	all = malloc(sizeof(t_all));
	pthread_mutex_init(&mutex, NULL);
	all->data = get_data(argv);
	all->data->mutex = mutex;
	thread = malloc(sizeof(pthread_t) * all->data->number_of_philosophers);
	create_threads(thread, all);
	for (int i = 0; i < all->data->number_of_philosophers; i++)
		pthread_join(thread[i], NULL);
	pthread_mutex_destroy(&mutex);
	return (0);
}
