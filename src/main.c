/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:38:47 by axelpeti          #+#    #+#             */
/*   Updated: 2025/07/08 14:50:46 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main (int ac, char **av)
{
	t_data	*data;
	t_philo	*philos;
 	int i;

	i = 0;
	get_time();
	 if (ac == 5 && (!verif_arg(av[1], av[2], av[3], av[4])))
	{
		data = init_data(av[1], av[2], av[3], av[4]);
		philos = malloc(sizeof(t_philo) * data->nb_philo);
		philos = init_philo(data, philos);
		while (1)
		{
			while (i < data->nb_philo)
			{
				pthread_create(&philos[i].thread_id, NULL, &thread_routine, &philos[i]);
				i++;
			}
		}
	}
	else
	{
		ft_putstr_fd("invalid argument", 2);
	}
}