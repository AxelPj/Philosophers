/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axelpeti <axelpeti@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 22:37:18 by axelpeti          #+#    #+#             */
/*   Updated: 2025/07/13 19:32:49 by axelpeti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_data
{
	int				nb_philo;
	int				time_to_sleep;
	int				time_to_eat;
	int				stop;
	pthread_mutex_t	write;
	pthread_mutex_t	inspect_data;
	pthread_mutex_t	inspect_philo;
	pthread_mutex_t	inspect_stop;
}	t_data;

typedef struct s_philo
{
	pthread_t		thread_id;
	long long		last_time_to_eat;
	long long		start;
	int				nb_food;
	int				id;
	int				time_to_sleep;
	int				time_to_eat;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
	int				dead;
}	t_philo;

typedef struct s_monitor
{
	pthread_t		thread_id;
	int				nb_philo;
	int				max_food;
	int				*tab;
	t_data			*data;
	int				time_to_die;
	t_philo			*philo;
	int				stop;
}	t_monitor;
//----------------Utils------------------//
char		*ft_itoa(int n);
void		ft_putstr_fd(char *s, int fd);
int			ft_isdigit(int c);
int			verif_nb(char *av);
int			ft_atoi(const char *str);
int			verif_arg(char *av1, char *av2, char *av3, char *av4);
int			verif_arg2(char *av5);
t_philo		*init_philo(t_data *data, t_philo *philos, char *sleep, char *eat);
t_monitor	*init_monitor(t_data *data, t_philo *philo, char *die, char *food);
t_data		*init_data(char *nb_ph);
//-------------------thread--------//
void		*thread_routine(void *arg);
int			taken_forks(t_philo *philo);
int			philo_eat(t_philo *philo);
int			philo_write(t_philo *philo, char *s);
long long	get_time(void);
int			verif_stop(t_philo *philo);
void		ft_sleep(long long sleep);
//-------------------supervisor--------//
int			check_monitor_death(t_monitor *monitor);
void		*supervisor_routine(void *arg);
int			verif_monitor_food(t_monitor *monitor);
#endif