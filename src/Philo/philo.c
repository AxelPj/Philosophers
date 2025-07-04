/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 15:19:46 by axelpeti          #+#    #+#             */
/*   Updated: 2025/07/04 19:20:43 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*thread_routine(void *arg, t_philo *philo)
{
	
	printf("routine du philo commencer philo numeros %lu\n", philo->thread_id);
	
	return (arg);
}