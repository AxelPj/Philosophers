/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:19:46 by axelpeti          #+#    #+#             */
/*   Updated: 2025/07/13 19:32:13 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_routine(void *arg)
{
	t_philo	*philo;
	int	forks_taken;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		ft_sleep(200);
	while (1)
	{
		if (verif_stop(philo))
			break ;
		if (philo_write(philo, "Thinking"))
			break ;
		if (verif_stop(philo))
			break ;
		forks_taken = taken_forks(philo);
		if (!forks_taken)
			continue ; // On repart de zéro si les forks n'ont pas été pris
		if (philo_eat(philo))
			break ;
		if (philo_write(philo, "Sleeping"))
			break ;
		ft_sleep(philo->time_to_sleep);
	}
	return (arg);
}

int	philo_eat(t_philo *philo)
{
	philo_write(philo, "Eating");
	pthread_mutex_lock(&philo->data->inspect_philo);
	philo->last_time_to_eat = get_time();
	philo->nb_food++;
	pthread_mutex_unlock(&philo->data->inspect_philo);
	ft_sleep(philo->time_to_eat);
	if (philo->id % 2 == 0)
	{
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	else
	{
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(&philo->left_fork);
	}
	return (0);
}


int	taken_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->left_fork);
		philo_write(philo, "has taken left fork");
		if (verif_stop(philo) == 1)
		{
			pthread_mutex_unlock(&philo->left_fork);
			return (0);
		}
		pthread_mutex_lock(philo->right_fork);
		philo_write(philo, "has taken right fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		philo_write(philo, "has taken right fork");
		if (verif_stop(philo) == 1)
		{
			pthread_mutex_unlock(philo->right_fork);
			return (0);
		}
		pthread_mutex_lock(&philo->left_fork);
		philo_write(philo, "has taken left fork");
	}
	return (1);
}


int	philo_write(t_philo *philo, char *s)
{
	if (verif_stop(philo) == 1)
		return (1);
	if (verif_stop(philo) == 0)
	{
		pthread_mutex_lock(&philo->data->write);
		printf("\033[33m""%lld  %d %s\n", (get_time() - philo->start),
			philo->id, s);
		pthread_mutex_unlock(&philo->data->write);
	}
	return (0);
}
