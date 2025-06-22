
#include "../includes/philo.h"

void	init_data(t_data *data, int philo_count)
{
	data->dead = 0;

	data->fork = malloc(sizeof(pthread_mutex_t) * philo_count);
	if (!data->fork)
	{
		printf("Malloc fail\n");
		return ;
	}
	pthread_mutex_init(&data->display_lock, NULL);
	pthread_mutex_init(&data->dead_lock, NULL);
	pthread_mutex_init(&data->meal_lock, NULL);
}

void	init_forks(pthread_mutex_t *forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}

void init_routine(t_philo *philo, char **av)
{
	philo->num_of_philos = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		philo->num_times_to_eat = ft_atoi(av[5]);
	else
		philo->num_times_to_eat = -1;

}

void	init_philo(t_data *data, t_philo *philos, char **av, size_t start_time)
{
	int	i = 0;

	while (i < ft_atoi(av[1]))
	{
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].meals_eaten = 0;
		init_routine(&philos[i], av);

		philos[i].start_time = start_time;
		philos[i].write_lock = &data->display_lock;
		philos[i].dead_lock = &data->dead_lock;
		philos[i].meal_lock = &data->meal_lock;
		philos[i].dead = &data->dead;
		philos[i].l_fork = &data->fork[i];
		if (i == 0)
			philos[i].r_fork = &data->fork[philos[i].num_of_philos - 1];
		else
			philos[i].r_fork = &data->fork[i - 1];

		pthread_mutex_lock(philos[i].meal_lock);
		philos[i].last_meal = start_time;
		pthread_mutex_unlock(philos[i].meal_lock);

		i++;
	}
}


