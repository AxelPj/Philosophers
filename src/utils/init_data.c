/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:46:34 by axelpeti          #+#    #+#             */
/*   Updated: 2025/07/05 17:57:21 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_data *init_data (char *nb_ph, char *time_to_die, char *time_to_sleep, char *time_to_eat)
{
	t_data *data;

	data = malloc(sizeof(t_data));
	data->dead_count = ft_atoi(time_to_die);
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
		pthread_mutex_init(&philo[i].left_fork, NULL);
		philo[i].right_fork = &philo[(i + 1) % data->nb_philo].left_fork;
		/* pthread_create(&philos[i].thread_id, NULL, &thread_routine, &philos[i]);
		usleep(10); */
		i++;
	}
}