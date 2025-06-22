
#include "../includes/philo.h"

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!dead_loop(philo))
	{
		eat(philo);
		dream(philo);
		think(philo);
	}
	return (pointer);
}

void	destroy_all(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&data->display_lock);
	pthread_mutex_destroy(&data->meal_lock);
	pthread_mutex_destroy(&data->dead_lock);
	while (i < data->philos[0].num_of_philos)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
}

int thread_create(t_data *data)
{
    pthread_t   monitor;
    int         i;

    i  = 0;
    while (i < data->philos[0].num_of_philos)
    {
        if (pthread_create(&data->philos[i].thread, NULL, &philo_routine, 
                &data->philos[i]) != 0)
            {
                printf("thread creation error\n");
                destroy_all(data);
            }
        i++;
    }
    if (pthread_create(&monitor, NULL, &ft_monitor, data->philos) != 0)
    {
        printf("Error : thread creation\n");
        destroy_all(data);
    }
    if (pthread_join(monitor, NULL) != 0)
    {
        printf("Error thread join\n");
        destroy_all(data);
    }
    i =0;
    while (i < data->philos[0].num_of_philos)
    {
        if (pthread_join(data->philos[i].thread, NULL) != 0)
        {
            printf("Error : join error");
            destroy_all(data);
        }
        i++;
    }
    return (0);
}

