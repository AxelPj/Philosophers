/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:38:47 by axelpeti          #+#    #+#             */
/*   Updated: 2025/07/15 11:33:39 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thread_run(t_data *data, t_philo *philos, t_monitor *monitor)
{
	int	i;

	i = 0;
	if (data->nb_philo == 1)
		pthread_create(&philos[i].thread_id, NULL, &one_thread, &philos[i]);
	else
	{
		while (i < data->nb_philo)
		{
			pthread_create(&philos[i].thread_id, NULL, &thread_routine,
				&philos[i]);
			i++;
		}
	}
	pthread_create(&monitor->thread_id, NULL, &supervisor_routine, monitor);
	pthread_join(monitor->thread_id, NULL);
	i = 0;
	while (i < data->nb_philo)
		pthread_join(philos[i++].thread_id, NULL);
	free(monitor->tab);
	free(monitor);
	free(data);
	free(philos);
}

int	main(int ac, char **av)
{
	t_data		*data;
	t_philo		*philos;
	t_monitor	*monitor;

	monitor = NULL;
	get_time();
	if (ac == 5 && (!verif_arg(av[1], av[2], av[3], av[4])))
	{
		data = init_data(av[1]);
		philos = malloc(sizeof(t_philo) * data->nb_philo);
		philos = init_philo(data, philos, av[3], av[4]);
		monitor = init_monitor(data, philos, av[2], NULL);
		thread_run(data, philos, monitor);
	}
	else if (ac == 6 && (!verif_arg(av[1], av[2], av[3], av[4]))
		&& (!verif_arg2(av[5])))
	{
		data = init_data(av[1]);
		philos = malloc(sizeof(t_philo) * data->nb_philo);
		philos = init_philo(data, philos, av[3], av[4]);
		monitor = init_monitor(data, philos, av[2], av[5]);
		thread_run(data, philos, monitor);
	}
	else
		ft_putstr_fd("invalid argument", 2);
}
