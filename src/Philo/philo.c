/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:19:46 by axelpeti          #+#    #+#             */
/*   Updated: 2025/07/08 18:50:35 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_routine(void *arg)
{
	t_philo *philo;
	long long time_count;

	time_count = 0;
	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		usleep(1000);
	pthread_mutex_lock(&philo->data->time);
	philo->start = get_time();
	pthread_mutex_unlock(&philo->data->time);
	while (time_count <= philo->data->time_to_die)
	{
		philo_write(philo, 1);
		philo_eat(philo);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		philo_write(philo, 3);
		usleep(philo->data->time_to_sleep * 1000);
		pthread_mutex_lock(&philo->data->time);
		philo->end = get_time();
		time_count = philo->start - philo->end;
		time_count -= philo->last_time_to_eat;
		pthread_mutex_unlock(&philo->data->time);
	}
	philo_write(philo, 4);
	return (arg);
}

void	philo_eat(t_philo *philo)
{
	if(philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&philo->left_fork);
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork);
		pthread_mutex_lock(philo->right_fork);
	}
	philo_write(philo, 2);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&philo->data->time);
	philo->last_time_to_eat = get_time();
	pthread_mutex_unlock(&philo->data->time);
	philo->nb_food++;
}

void	philo_write(t_philo *philo, int bool)
{
	pthread_mutex_lock(&philo->data->write);
	if (bool == 1)
		printf("%lldms philo id : %d pense\n", get_time() - philo->start, philo->id);
	else if (bool == 2)
		printf("%lldms philo id %d dort\n", get_time() - philo->start, philo->id);
	else if (bool == 3)
		printf("%lldms philo id %d mange\n", get_time() - philo->start, philo->id);
	else if (bool == 4)
		printf("%lldms philo id %d meurt\n", get_time() - philo->start, philo->id);
	pthread_mutex_unlock(&philo->data->write);
}

void	*supervisor_routine(void *arg)
{
	t_monitor *monitor;
	int i;

	i = 1;
	monitor = (t_philo *)arg;
	while(monitor->philo[i]->last_time_to_eat < monitor->philo[i]->start - monitor->philo[i]->end)
	{
		i = 1
		while (monitor->philo[i])
		{
			
			i++;
		}
	}
}