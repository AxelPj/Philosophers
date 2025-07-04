/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:38:47 by axelpeti          #+#    #+#             */
/*   Updated: 2025/07/04 19:03:38 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main (int ac, char **av)
{
	t_data	*data;
	pthread_t	*thread;
	int i;
	t_philo	philo;

	thread = malloc (5 * sizeof (pthread_t));
	i = 0;
	if (ac == 5 && (!verif_arg(av[1], av[2], av[3], av[4])))
	{
		data = init_data(av[1], av[2], av[3], av[4]);
		while (i < data->nb_philo)
		{
			pthread_create(&thread[i], NULL, &thread_routine, NULL);
			i++;
		}
	}
	else
		ft_putstr_fd("invalid argument", 2);
}