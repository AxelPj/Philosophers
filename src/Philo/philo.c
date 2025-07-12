/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:19:46 by axelpeti          #+#    #+#             */
/*   Updated: 2025/07/13 00:21:21 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->inspect_philo);
	philo->start = get_time();
	philo->last_time_to_eat = philo->start;
	pthread_mutex_unlock(&philo->data->inspect_philo);
 	if (philo->id % 2 != 0)
		usleep(1000);
	while (1)
	{
		if (philo_write(philo, "thinking"))
			break ;
		if (philo->id % 2 == 0)
			philo_eat_pair(philo);
		else
			philo_eat_impair(philo);
		if (philo_write(philo, "sleeping"))
			break ;
		usleep(philo->time_to_sleep);
		if (verif_stop(philo))
			break ;
	}
	return (arg);
}

void	philo_eat_pair(t_philo *philo)
{
		pthread_mutex_lock(&philo->left_fork);
		philo_write(philo, "has taken a fork");
		if (verif_stop(philo) == 1)	
			return (pthread_mutex_unlock(&philo->left_fork), (void) 0);
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(&philo->data->inspect_philo);
		philo->last_time_to_eat = get_time() + philo->time_to_eat;
		pthread_mutex_unlock(&philo->data->inspect_philo);
		philo_write(philo, "has taken a fork");
		philo_write(philo, "eating");
		ft_sleep(philo->time_to_eat);
		pthread_mutex_unlock(&philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_lock(&philo->data->inspect_philo);
		philo->last_time_to_eat = get_time();
		philo->nb_food++;
		pthread_mutex_unlock(&philo->data->inspect_philo);
}

void 	philo_eat_impair(t_philo *philo)
{
	pthread_mutex_lock(philo->right_fork);
	philo_write(philo, "has taken a fork");
	if (verif_stop(philo) == 1)
		return (pthread_mutex_unlock(philo->right_fork), (void) 0);
	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(&philo->data->inspect_philo);
	philo->last_time_to_eat = get_time() + philo->time_to_eat;
	pthread_mutex_unlock(&philo->data->inspect_philo);
	philo_write(philo, "has taken a fork");
	philo_write(philo, "eating");
	ft_sleep(philo->time_to_eat);
	pthread_mutex_unlock(&philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&philo->data->inspect_philo);
	philo->nb_food++;
	philo->last_time_to_eat = get_time();
	pthread_mutex_unlock(&philo->data->inspect_philo);
}

int	philo_write(t_philo *philo, char *s)
{
	pthread_mutex_lock(&philo->data->write);
	if (verif_stop(philo) == 1)
		return (pthread_mutex_unlock(&philo->data->write), 1);
	printf("\033[33m""%lld  %d %s\n", (get_time() - philo->start), philo->id, s);
	pthread_mutex_unlock(&philo->data->write);
	return (0);
}

void	*supervisor_routine(void *arg)
{
	t_monitor	*monitor;
	long long	time;
	int			i;

	monitor = (t_monitor *)arg;
	while (monitor->stop == 0)
	{
		i = 0;
		while (i < monitor->nb_philo && monitor->stop == 0)
		{
			pthread_mutex_lock(&monitor->data->inspect_philo);
			time = monitor->philo[i].last_time_to_eat;
			pthread_mutex_unlock(&monitor->data->inspect_philo);
printf("DEBUG: philo %d last_time_to_eat = %lld, now = %lld, diff = %lld, time_to_die = %lld\n",
       i, time, get_time(), get_time() - time, monitor->data->time_to_die);
			if (monitor->time_to_die < (get_time() - time))
			{
				philo_write(&monitor->philo[i], "dead");
				pthread_mutex_lock(&monitor->data->inspect_data);
				monitor->data->stop = 1;
				pthread_mutex_unlock(&monitor->data->inspect_data);
				monitor->stop = 1;
			}
			i++;
			usleep(100);
		}
	}
	return (NULL);
}
int verif_stop(t_philo *philo)
{
	int	food;

	pthread_mutex_lock(&philo->data->inspect_philo);
	food = philo->nb_food;
	pthread_mutex_unlock(&philo->data->inspect_philo);
	pthread_mutex_lock(&philo->data->inspect_data);
	if (philo->data->stop == 1 || food == philo->data->max_food)
	{
		pthread_mutex_unlock(&philo->data->inspect_data);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->inspect_data);
	return (0);
}
void	ft_sleep(long long time_in_ms)
{
	long long	start;

	start = get_time();
	if (time_in_ms > 10)
	    usleep((time_in_ms - 10) * 1000);
	while ((get_time() - start) < time_in_ms)
	    usleep(100);
}
