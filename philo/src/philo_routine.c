/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garside <garside@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:15:59 by garside           #+#    #+#             */
/*   Updated: 2025/06/24 19:48:04 by garside          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	alive_check(t_philo *philo)
{
	int	status;

	pthread_mutex_lock(philo->dead_lock);
	status = !(*philo->dead);
	pthread_mutex_unlock(philo->dead_lock);
	return (status);
}

int	dead_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 != 0)
		ft_usleep(1);
	while (alive_check(philo))
	{
		if (*philo->dead)
			break ;
		if (philo->num_times_to_eat != -1)
		{
			pthread_mutex_lock(philo->meal_lock);
			if (philo->meals_eaten >= philo->num_times_to_eat)
			{
				pthread_mutex_unlock(philo->meal_lock);
				break ;
			}
			pthread_mutex_unlock(philo->meal_lock);
		}
		eat(philo);
		dream(philo);
		think(philo);
	}
	return (NULL);
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

int	thread_create(t_data *data)
{
	pthread_t	monitor;
	int			i;

	i = 0;
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
	i = 0;
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
