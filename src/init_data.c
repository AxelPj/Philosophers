/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:46:34 by axelpeti          #+#    #+#             */
/*   Updated: 2025/07/14 12:38:23 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data	*init_data(char *nb_ph)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	data->stop = 0;
	data->nb_philo = ft_atoi(nb_ph);
	pthread_mutex_init(&data->write, NULL);
	pthread_mutex_init(&data->inspect_philo, NULL);
	pthread_mutex_init(&data->inspect_data, NULL);
	pthread_mutex_init(&data->inspect_stop, NULL);
	return (data);
}

t_philo	*init_philo(t_data *data, t_philo *philos, char *eat, char *sleep)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		philos[i].id = i + 1;
		philos[i].nb_food = 0;
		philos[i].data = data;
		philos[i].time_to_sleep = ft_atoi(sleep);
		philos[i].time_to_eat = ft_atoi(eat);
		pthread_mutex_init(&philos[i].left_fork, NULL);
		philos[i].start = get_time();
		philos[i].last_time_to_eat = philos->start;
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

t_monitor	*init_monitor(t_data *data, t_philo *philo, char *die, char *food)
{
	t_monitor	*monitor;
	int			i;

	i = 0;
	monitor = malloc(sizeof(t_monitor));
	if (food)
		monitor->max_food = ft_atoi(food);
	else
		monitor->max_food = -1;
	monitor->philo = philo;
	monitor->time_to_die = ft_atoi(die);
	monitor->data = data;
	monitor->nb_philo = monitor->data->nb_philo;
	monitor->stop = 0;
	monitor->tab = malloc(monitor->data->nb_philo * sizeof(int));
	while (i < monitor->data->nb_philo)
	{
		monitor->tab[i] = 0;
		i++;
	}
	return (monitor);
}
