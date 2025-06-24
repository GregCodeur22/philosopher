/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garside <garside@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:22:55 by garside           #+#    #+#             */
/*   Updated: 2025/06/24 13:04:48 by garside          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				num_of_philos;
	int				id;
	int				eating;
	int				meals_eaten;
	long long		last_meal;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	long long		start_time;
	int				num_times_to_eat;
	int				*dead;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*write_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*meal_lock;
}					t_philo;

typedef struct s_data
{
	int				dead;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	meal_lock;
	pthread_mutex_t	display_lock;
	pthread_mutex_t	*fork;
	t_philo			*philos;
}					t_data;

// main
int					ft_usleep(size_t milliseconds);
int					ft_atoi(const char *str);
long long			get_current_time(void);
int					valid_param(char **av);

// init.c
void				init_data(t_data *data, int philo_count);
void				init_forks(pthread_mutex_t *forks, int philo_num);
void				init_routine(t_philo *philo, char **av);
void				init_philo(t_data *data, t_philo *philos, char **av,
						long long start_time);

// monitor.c
void				*ft_monitor(void *pointer);
void				print_message(char *str, t_philo *philo, int id);
int					philosopher_dead(t_philo *philo, size_t time_to_die);
int					check_if_dead(t_philo *philos);
int					check_if_all_ate(t_philo *philos);

// thread.c
int					thread_create(t_data *data);
void				*philo_routine(void *pointer);
int					dead_loop(t_philo *philo);

// action
void				think(t_philo *philo);
void				dream(t_philo *philo);
void				eat(t_philo *philo);

#endif
