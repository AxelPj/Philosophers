/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:46:34 by axelpeti          #+#    #+#             */
/*   Updated: 2025/07/12 23:57:55 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


t_data	*init_data (char *nb_ph, char *max_food)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	if (max_food)
		data->max_food = ft_atoi(max_food);
	else
		data->max_food = -1;
	data->stop = 0;
	data->nb_philo = ft_atoi(nb_ph);
	pthread_mutex_init(&data->time, NULL);
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->inspect_philo, NULL);
	pthread_mutex_init(&data->inspect_data, NULL);
	return (data);
}

t_philo	*init_philo(t_data *data, t_philo *philos, char *time_to_sleep , char *time_to_eat)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].last_time_to_eat = 0;
		philos[i].nb_food = 0;
		philos[i].data = data;
		philos[i].dead = 0;
		philos[i].time_to_sleep = ft_atoi(time_to_sleep);
		philos[i].time_to_eat = ft_atoi(time_to_eat);
		pthread_mutex_init(&philos[i].left_fork, NULL);
		i++;
	}
	i = 0;
	while (i < data->nb_philo)
	{
		philos[i].right_fork = &philos[(i + 1) % data->nb_philo].left_fork;
		i++;	
	}
	return (philos);
}

 t_monitor	*init_monitor(t_data *data, t_philo *philo, char *time_to_die)
{
	t_monitor	*monitor;

	monitor = malloc(sizeof(t_monitor));
	monitor->philo = philo;
	monitor->time_to_die = ft_atoi(time_to_die);
	monitor->data = data;
	monitor->nb_philo = monitor->data->nb_philo;
	monitor->stop = 0;
	return (monitor);
}
