/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garside <garside@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/23 18:14:25 by garside           #+#    #+#             */
/*   Updated: 2025/06/23 18:23:27 by garside          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	res;

	sign = 1;
	res = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	if (*str == '+')
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * sign);
}

long long	get_current_time(void)
{
	struct timeval	time;
	long long		time_ms;

	if (gettimeofday(&time, NULL) == -1)
		return (0);
	time_ms = ((long long)time.tv_sec * 1000) + (time.tv_usec / 1000);
	return (time_ms);
}

int	check_arg_content(char *arg)
{
	int	i;

	i = 0;
	while (arg[i] != '\0')
	{
		if (arg[i] < '0' || arg[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	valid_param(char **av)
{
	if (ft_atoi(av[1]) > 200 || ft_atoi(av[1]) <= 0
		|| check_arg_content(av[1]) == 1)
		return (write(2, "Invalid philosophers number\n", 29), 1);
	if (ft_atoi(av[2]) <= 0 || check_arg_content(av[2]) == 1)
		return (write(2, "Invalid time to die\n", 21), 1);
	if (ft_atoi(av[3]) <= 0 || check_arg_content(av[3]) == 1)
		return (write(2, "Invalid time to eat\n", 21), 1);
	if (ft_atoi(av[4]) <= 0 || check_arg_content(av[4]) == 1)
		return (write(2, "Invalid time to sleep\n", 23), 1);
	if (av[5] && (ft_atoi(av[5]) < 0 || check_arg_content(av[5]) == 1))
		return (write(2, "Invalid number of times each philosopher must eat\n",
				51), 1);
	return (0);
}

int	main(int ac, char **av)
{
	t_data		*data;
	t_philo		*philo;
	int			philo_count;
	long long	start_time;

	start_time = get_current_time();
	if (ac != 5 && ac != 6)
		return (printf("Error: bad number of arguments\n"), 1);
	if (valid_param(av) == 1)
		return (1);
	philo_count = ft_atoi(av[1]);
	data = malloc(sizeof(t_data));
	if (!data)
		return (printf("Malloc fail for data\n"), 1);
	philo = malloc(sizeof(t_philo) * philo_count);
	if (!philo)
		return (printf("Malloc fail for philo\n"), 1);
	data->philos = philo;
	init_data(data, philo_count);
	init_forks(data->fork, philo_count);
	init_philo(data, philo, av, start_time);
	thread_create(data);
	free(data->fork);
	free(philo);
	free(data);
	return (0);
}
