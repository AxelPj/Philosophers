/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 17:42:57 by axelpeti          #+#    #+#             */
/*   Updated: 2025/07/13 17:28:34 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	i = 0;
	while (s[i])
	{
		write (fd, &s[i], 1);
		i++;
	}
}

long long	get_time(void)
{
	struct timeval	tv;
	long long		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_usec / 1000) + (tv.tv_sec * 1000);
	return (time);
}

int	verif_stop(t_philo *philo)
{
	int	food;

	pthread_mutex_lock(&philo->data->inspect_stop);
	if (philo->data->stop == 1)
	{
		pthread_mutex_unlock(&philo->data->inspect_stop);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->inspect_stop);
	pthread_mutex_lock(&philo->data->inspect_philo);
	food = philo->nb_food;
	pthread_mutex_unlock(&philo->data->inspect_philo);
	pthread_mutex_lock(&philo->data->inspect_stop);
	if (philo->data->stop == 1)
	{
		pthread_mutex_unlock(&philo->data->inspect_stop);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->inspect_stop);
	return (0);
}

void	ft_sleep(long long milliseconds)
{
	long long	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(200);
}
