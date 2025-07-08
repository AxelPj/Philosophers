#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
#include <sys/time.h>


typedef struct s_data
{
	int				nb_philo;
	int				time_to_die ;
	int				time_to_sleep;
	int				time_to_eat;
	long			milliseconds;
	pthread_mutex_t	write;
	pthread_mutex_t	time;
}	t_data;

typedef struct s_philo
{
	pthread_t		thread_id;
	long long		start;
	long long		end;
	long long		last_time_to_eat;
	int				nb_food;
	int				id;
	pthread_mutex_t	left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}	t_philo;

typedef struct s_monitor
{
	pthread_t		thread_id;
	t_data	*data;
	t_philo	*philo;
	int		stop;
}	t_monitor;
//----------------Utils------------------//
char		*ft_itoa(int n);
void		ft_putstr_fd(char *s, int fd);
int			ft_isdigit(int c);
int			verif_nb(char *av);
int			ft_atoi(const char *str);
int			verif_arg(char *av1, char *av2, char *av3, char *av4);
t_philo 	*init_philo(t_data *data, t_philo *philos);
t_data		*init_data (char *nb_ph, char *time_to_die, char *time_to_sleep, char *time_to_eat);
//-------------------thread--------//
void		*thread_routine(void *arg);
void		philo_eat(t_philo *philo);
void		philo_write(t_philo *philo, int bool);
long long	get_time();
#endif