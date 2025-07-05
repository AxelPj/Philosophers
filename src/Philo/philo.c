/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:19:46 by axelpeti          #+#    #+#             */
/*   Updated: 2025/07/05 17:50:26 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_routine(void *arg)
{
	t_philo *philo;
	philo = (t_philo *)arg;
	int i = 0;
	get_time
	while ()
	{
		pthread_mutex_lock;
		printf("philo id %d pense\n", philo->id);
		printf("philo id %d mange\n", philo->id);
		printf("philo id %d dort\n", philo->id);
		pthread_mutex_unlock;
		i++;
	}
	return (arg);
}