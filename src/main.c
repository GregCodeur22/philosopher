/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garside <garside@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 17:38:48 by garside           #+#    #+#             */
/*   Updated: 2025/06/17 18:34:33 by garside          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int main(int ac, char **av)
{
    t_data *data;

    if (init_data(&data, ac, av) == 1) {
        return (1);
    }

    if (valid_param(data, ac) == 1) {
        free_data(data);
        return (1);
    }

    if (data->nbr_philo > 200) {
        printf("Il y a trop de philosophes\n");
        free_data(data);
        return (1);
    }

    print_param(data);
    destroy_mutex(data);
    free_data(data);
    return (0);
}

