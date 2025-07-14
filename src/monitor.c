/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 17:18:03 by axelpeti          #+#    #+#             */
/*   Updated: 2025/07/14 12:03:48 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*supervisor_routine(void *arg)
{
	t_monitor	*monitor;

	monitor = (t_monitor *)arg;
	while (1)
	{
		if (check_monitor_death(monitor))
			break ;
		if (monitor->max_food != -1)
		{
			if (verif_monitor_food(monitor))
			{
				write (1, "If all the philosophers have eaten enough\n", 42);
				break ;
			}
		}
	}
	return (NULL);
}

int	verif_monitor_food(t_monitor *monitor)
{
	int	food;
	int	i;

	i = 0;
	while (i < monitor->nb_philo)
	{
		pthread_mutex_lock(&monitor->philo[i].data->inspect_philo);
		food = monitor->philo[i].nb_food;
		pthread_mutex_unlock(&monitor->philo[i].data->inspect_philo);
		if (food >= monitor->max_food)
			monitor->tab[i] = 1;
		i++;
	}
	i = 0;
	while (i < monitor->nb_philo)
	{
		if (monitor->tab[i] == 0)
			return (0);
		i++;
	}
	monitor->data->stop = 1;
	return (1);
}

int	check_monitor_death(t_monitor *monitor)
{
	int			i;
	long long	time;

	i = 0;
	while (i < monitor->nb_philo)
	{
		pthread_mutex_lock(&monitor->data->inspect_philo);
		time = monitor->philo[i].last_time_to_eat;
		pthread_mutex_unlock(&monitor->data->inspect_philo);
		if (monitor->time_to_die < (get_time() - time))
		{
			philo_write(&monitor->philo[i], "Dead");
			pthread_mutex_lock(&monitor->data->inspect_stop);
			monitor->data->stop = 1;
			pthread_mutex_unlock(&monitor->data->inspect_stop);
			monitor->stop = 1;
			return (1);
		}
		i++;
		usleep(500);
	}
	return (0);
}
