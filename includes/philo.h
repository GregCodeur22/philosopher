#ifndef PHILO_
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_mutex_t	*fork;
}					t_philo;

typedef struct s_data
{
	int				nbr_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				each_eat;
	t_philo			*philo;
}					t_data;

// main
int					is_valid_param(int n);

// main_utils
int					valid_param(t_data *data, int ac);
void				print_param(t_data *data);
void				destroy_mutex(t_data *data);
void				free_data(t_data *data);
int					init_data(t_data **data, int ac, char **av);

// init
int					ft_safe_atoi(const char *str, int *out);
int					is_number(const char *str);
int					is_valid_param(int n);
int					init_param(t_data *philo, int ac, char **av);
int					init_fork(t_data *data);

#endif
