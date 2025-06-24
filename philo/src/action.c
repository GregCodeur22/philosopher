#include "../includes/philo.h"

void	think(t_philo *philo)
{
	if (dead_loop(philo))
		return;
	ft_usleep(1);
	print_message("is thinking", philo, philo->id);
}

void	dream(t_philo *philo)
{
	if (dead_loop(philo))
		return;
	print_message("is sleeping", philo, philo->id); 
	ft_usleep(philo->time_to_sleep);
}

int alive_check(t_philo *philo)
{
    int status;
    pthread_mutex_lock(philo->dead_lock);
    status = !(*philo->dead);
    pthread_mutex_unlock(philo->dead_lock);
    return status;
}


void take_forks(t_philo *philo)
{
	if (philo->num_of_philos == 1)
		{
				pthread_mutex_lock(philo->l_fork);
				print_message("has taken a fork", philo, philo->id);
				ft_usleep(philo->time_to_die + 1);
				pthread_mutex_unlock(philo->l_fork);
				return;
		}
    if (philo->id == philo->num_of_philos)
    {
        pthread_mutex_lock(philo->l_fork);   // Prend d'abord la gauche
        print_message("has taken a fork", philo, philo->id);
        pthread_mutex_lock(philo->r_fork);  // Puis la droite
        print_message("has taken a fork",philo , philo->id);
    }
    // Tous les autres philosophes
    else
    {
        pthread_mutex_lock(philo->r_fork);  // Prend d'abord la droite
        print_message("has taken a fork", philo ,philo->id);
        pthread_mutex_lock(philo->l_fork);   // Puis la gauche
        print_message("has taken a fork", philo, philo->id);
    }
}

void release_forks(t_philo *philo)
{
    if (philo->num_of_philos == 1)
        return;
    pthread_mutex_unlock(philo->l_fork);
    pthread_mutex_unlock(philo->r_fork);
}

void eat(t_philo *philo)
{
    if (!alive_check(philo))
        return;
    take_forks(philo);
    if (!alive_check(philo))
    {
        release_forks(philo);
        return;
    }
    pthread_mutex_lock(philo->meal_lock);
    philo->last_meal = get_current_time();
		philo->meals_eaten++;
    pthread_mutex_unlock(philo->meal_lock);
    print_message("is eating", philo, philo->id);
    ft_usleep(philo->time_to_eat);
    release_forks(philo);
}


