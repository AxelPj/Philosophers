#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_data
{
	int			nb_philo;
	int			dead_count;
	int			time_to_sleep;
	int			time_to_eat;
}	t_data;

typedef struct s_philo
{
	pthread_t	thread_id;
	pthread_t	*threads;
	int			last_time_to_eat;
} t_philo;

//----------------Utils------------------//
char		*ft_itoa(int n);
void	ft_putstr_fd(char *s, int fd);
int			ft_isdigit(int c);
int			verif_nb(char *av);
int			ft_atoi(const char *str);
int	verif_arg(char *av1, char *av2, char *av3, char *av4);
t_data *init_data (char *nb_ph, char *time_to_die, char *time_to_sleep, char *time_to_eat);
//-------------------thread--------//
void	*thread_routine(void *arg, t_philo *philo);
#endif