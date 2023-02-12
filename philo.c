/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afalconi <afalconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:40:04 by ccolaiac          #+#    #+#             */
/*   Updated: 2023/02/12 17:16:00 by afalconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_one(t_everyone *everyone)
{
	int		i;

	i = 0;
	everyone->philo = malloc(sizeof(t_one) * everyone->num_philo);
	if (!everyone->philo)
		return ;
	while (i < everyone->num_philo)
	{
		everyone->philo[i] = malloc(sizeof(t_one));
		if (!everyone->philo[i])
			return ;
		everyone->philo[i]->id = i;
		everyone->philo[i]->time_to_eat = everyone->time_to_eat;
		everyone->philo[i]->time_to_sleep = everyone->time_to_sleep;
		everyone->philo[i]->time_to_die = everyone->time_to_die;
		everyone->philo[i]->num_of_times_ate = 0;
		everyone->philo[i]->t = everyone;
		everyone->philo[i]->time_last_meal = 0;
		everyone->philo[i]->philo_status = 0;
		i++;
	}
}

long long	delta_time(long long time)
{
	if (time > 0)
		return (get_time() - time);
	return (0);
}

long long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * (uint64_t)1000) + (time.tv_usec / (uint64_t)1000));
}

static int	init_all(char **av, t_everyone *everyone)
{
	everyone->num_philo = ft_atoi(av[1]);
	everyone->time_to_die = ft_atoi(av[2]);
	everyone->time_to_eat = ft_atoi(av[3]);
	everyone->time_to_sleep = ft_atoi(av[4]);
	everyone->end = 0;
	everyone->start = get_time();
	pthread_mutex_init(&everyone->write, NULL);
	if (av[5])
		everyone->num_of_times_eat = ft_atoi(av[5]);
	everyone->forks = malloc(sizeof(pthread_mutex_t) * everyone->num_philo);
	init_one(everyone);
	init_fork(everyone);
	return (TRUE);
}

int	main(int ac, char **av)
{
	t_everyone	*everyone;

	everyone = malloc(sizeof(t_everyone));
	if (!everyone)
		return (1);
	if (!check_inputs(ac, av))
	{
		printf("Error inputs ! \n");
		return (FALSE);
	}
	init_all(av, everyone);
	init_philo(everyone);
}
