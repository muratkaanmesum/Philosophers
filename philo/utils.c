/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/23 20:45:57 by mmesum            #+#    #+#             */
/*   Updated: 2023/01/26 08:45:12 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *str)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

unsigned long	get_current_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

unsigned long	get_passed_time(unsigned long begin)
{
	return (get_current_time() - begin);
}

void	print_message(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->data->print);
	if (philo->data->is_dead != 0)
	{
		pthread_mutex_unlock(&philo->data->print);
		return ;
	}
	printf("%lu %d %s\n", get_passed_time(philo->data->start_time), philo->id,
			message);
	pthread_mutex_unlock(&philo->data->print);
}

void	smart_sleep(int time, t_data *data)
{
	unsigned long	begin;

	begin = get_current_time();
	while (get_passed_time(begin) <= (unsigned long)time && is_dead(data) == 0)
		usleep(100);
}
