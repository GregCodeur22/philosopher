/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garside <garside@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:35:47 by garside           #+#    #+#             */
/*   Updated: 2025/06/17 18:38:15 by garside          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	valid_param(t_data *data, int ac)
{
	if (!is_valid_param(data->nbr_philo) || !is_valid_param(data->time_to_die)
		|| !is_valid_param(data->time_to_eat)
		|| !is_valid_param(data->time_to_sleep) || (ac == 6
			&& !is_valid_param(data->each_eat)))
	{
		printf("Erreur : tous les paramètres doivent être des entiers positifs\n");
		return (1);
	}
	return (0);
}

void	print_param(t_data *data)
{
	printf("Paramètres lus :\n");
	printf("philosophes : %d\n", data->nbr_philo);
	printf("Temps mourir : %d\n", data->time_to_die);
	printf("Temps manger : %d\n", data->time_to_eat);
	printf("Temps dormir : %d\n", data->time_to_sleep);
	printf("Repas requis : %d\n", data->each_eat);
}

void	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbr_philo)
	{
		pthread_mutex_destroy(&data->philo->fork[i]);
		i++;
	}
}

void	free_data(t_data *data)
{
	free(data->philo->fork);
	free(data->philo);
	free(data);
}

int	init_data(t_data **data, int ac, char **av)
{
	if (ac != 5 && ac != 6)
	{
		printf("Usage: ./philo nbr_philo time_to_die time_to_eat time_to_sleep [each_eat]\n");
		return (1);
	}
	*data = malloc(sizeof(t_data));
	if (!*data)
		return (1);
	(*data)->philo = malloc(sizeof(t_philo));
	if (!(*data)->philo)
	{
		free(*data);
		return (1);
	}
	init_param(*data, ac, av);
	if (init_fork(*data))
	{
		printf("Erreur lors de l'init des fourchettes\n");
		free((*data)->philo);
		free(*data);
		return (1);
	}
	return (0);
}
