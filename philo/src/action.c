/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garside <garside@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 19:46:06 by garside           #+#    #+#             */
/*   Updated: 2025/06/24 19:56:58 by garside          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

void	think(t_philo *philo)
{
	if (!alive_check(philo))
		return ;
	ft_usleep(1);
	print_message("is thinking", philo, philo->id);
}

void	dream(t_philo *philo)
{
	long long	start;

	if (!alive_check(philo))
		return ;
	print_message("is sleeping", philo, philo->id);
	start = get_current_time();
	while (get_current_time() - start < philo->time_to_sleep)
	{
		if (!alive_check(philo))
			return ;
		ft_usleep(1);
	}
}

void	take_forks(t_philo *philo)
{
	if (philo->num_of_philos == 1)
	{
		pthread_mutex_lock(philo->l_fork);
		print_message("has taken a fork", philo, philo->id);
		ft_usleep(philo->time_to_die + 1);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	if (philo->id == philo->num_of_philos)
	{
		pthread_mutex_lock(philo->l_fork);
		print_message("has taken a fork", philo, philo->id);
		pthread_mutex_lock(philo->r_fork);
		print_message("has taken a fork", philo, philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->r_fork);
		print_message("has taken a fork", philo, philo->id);
		pthread_mutex_lock(philo->l_fork);
		print_message("has taken a fork", philo, philo->id);
	}
}

void	release_forks(t_philo *philo)
{
	if (philo->num_of_philos == 1)
		return ;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	eat(t_philo *philo)
{
	long long	start;

	if (!alive_check(philo))
		return ;
	take_forks(philo);
	if (!alive_check(philo))
		return (release_forks(philo));
	pthread_mutex_lock(philo->meal_lock);
	philo->last_meal = get_current_time();
	philo->meals_eaten++;
	pthread_mutex_unlock(philo->meal_lock);
	print_message("is eating", philo, philo->id);
	start = get_current_time();
	while (get_current_time() - start < philo->time_to_eat)
	{
		if (!alive_check(philo))
		{
			release_forks(philo);
			return ;
		}
		ft_usleep(1);
	}
	release_forks(philo);
}
