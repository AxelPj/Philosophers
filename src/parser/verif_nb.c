/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_nb.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/04 14:39:09 by axelpeti          #+#    #+#             */
/*   Updated: 2025/07/12 22:38:37 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	verif_arg(char *av1, char *av2, char *av3, char *av4)
{
	if (verif_nb(av1) || verif_nb(av2) || verif_nb(av3) || verif_nb(av4))
		return (1);
	else if (ft_atoi(av1) == 0)
		return (1);
	return (0);
}
int	verif_arg2(char *av5)
{
	if (verif_nb(av5))
		return (1);
	return (0);
}

int	verif_nb(char *av)
{
	int i;

	i = 0;
	while (av[i])
	{
		if (!ft_isdigit(av[i]))
			return (1);
		i++;
	}
	return (0);
}
