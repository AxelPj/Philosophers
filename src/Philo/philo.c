/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:19:46 by axelpeti          #+#    #+#             */
/*   Updated: 2025/07/06 18:08:43 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (1)
	{
		printf("philo id %d pense\n", philo->id);
		if(philo->id % 2 == 0 /* && rajouter le calcul du temps de vie restant*/)
		{
			pthread_mutex_lock(philo->right_fork);
			pthread_mutex_lock(&philo->left_fork);
		}
		else
		{
			pthread_mutex_lock(&philo->left_fork);
			pthread_mutex_lock(philo->right_fork);
		}	
			printf("philo id %d mange\n", philo->id);
			/* philo->last_time_to_eat = get_time(); */
			usleep(philo->data->time_to_eat);
			pthread_mutex_unlock(&philo->left_fork);
			pthread_mutex_unlock(philo->right_fork);
			printf("philo id %d dort\n", philo->id);
			usleep(philo->data->time_to_sleep);
	}
	return (arg);
}
/* 
void	philo_eat(t_philo philos)
{
	if 
} */