/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:46:34 by axelpeti          #+#    #+#             */
/*   Updated: 2025/07/04 18:56:00 by axelpeti         ###   ########.fr       */
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

