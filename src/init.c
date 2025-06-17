/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garside <garside@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:09:05 by garside           #+#    #+#             */
/*   Updated: 2025/06/17 18:30:52 by garside          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_atoi(const char *str)
{
	int	res;

	res = 0;
	while (*str >= '0' && *str <= '9')
		res = res * 10 + (*str++ - '0');
	return (res);
}

int	is_number(const char *str)
{
	if (!str || *str == '\0')
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

int	is_valid_param(int n)
{
	return (n > 0);
}

int	init_param(t_data *philo, int ac, char **av)
{
	philo->nbr_philo = ft_atoi(av[1]);
	philo->time_to_die = ft_atoi(av[2]);
	philo->time_to_eat = ft_atoi(av[3]);
	philo->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		philo->each_eat = ft_atoi(av[5]);
	else
		philo->each_eat = -1;
	return (0);
}

int	init_fork(t_data *data)
{
	int	i;

	i = 0;
	data->philo->fork = malloc(sizeof(pthread_mutex_t) * data->nbr_philo);
	if (!data->philo->fork)
		return (1);
	while (i < data->nbr_philo)
	{
		if (pthread_mutex_init(&data->philo->fork[i], NULL) != 0)
		{
			printf("Ereur l'ors de l'initialisation des mutex\n");
			free(data->philo->fork);
			return (1);
		}
		i++;
	}
	return (0);
}
