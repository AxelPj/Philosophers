/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:46:34 by axelpeti          #+#    #+#             */
/*   Updated: 2025/07/09 00:11:51 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data *init_data (char *nb_ph, char *time_to_die, char *time_to_sleep, char *time_to_eat)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	data->time_to_die = ft_atoi(time_to_die);
	data->nb_philo = ft_atoi(nb_ph);
	data->time_to_sleep = ft_atoi(time_to_sleep);
	data->time_to_eat = ft_atoi(time_to_eat);
	return (data);
}

t_philo *init_philo(t_data *data, t_philo *philos)
{
	int	i;
	i = 0;
	while (i < data->nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].last_time_to_eat = 0;
		philos[i].nb_food = 0;
		philos[i].data = data;
		pthread_mutex_init(&philos[i].left_fork, NULL);
		pthread_mutex_init(&data->time, NULL);
		pthread_mutex_init(&data->write, NULL);
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

t_monitor	*init_monitor(t_data *data, t_philo *philo, t_monitor *monitor)
{
	monitor = malloc(sizeof(t_monitor));
	monitor->philo = philo;
	monitor->data = data;
	monitor->stop = 0;
	return (monitor);
}
