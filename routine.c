/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afalconi <afalconi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 13:19:23 by aliburdi          #+#    #+#             */
/*   Updated: 2023/02/12 21:30:31 by afalconi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_fork(t_everyone *t)
{
	int	i;

	i = 0;
	while (i < t->num_philo)
	{
		pthread_mutex_init(&t->forks[i], NULL);
		i++;
	}
}

void	ft_write(int id, t_everyone *t, char *str)
{
	pthread_mutex_lock(&t->write);
	printf("%lld %d %s\n", (get_time() - t->start), id + 1, str);
	if (str[0] != 'd')
		pthread_mutex_unlock(&t->write);
}

void	take_forks(int id, t_everyone *t)
{
	pthread_mutex_lock(&t->forks[id]);
	ft_write(id, t, "has taken the left fork!");
	pthread_mutex_lock(&t->forks[(id + 1) % t->num_philo]);
	ft_write(id, t, "has taken the right fork!");
}

void	eat(int id, t_everyone *t)
{
	t->philo[id]->time_last_meal = get_time();
	ft_write(id, t, "is eating!");
	while ((get_time() - t->philo[id]->time_last_meal) < t->time_to_eat)
		continue ;
	t->philo[id]->time_last_meal = get_time();
	if (t->num_of_times_eat != 0)
		t->num_of_times_eat--;
	// if (t->num_of_times_eat == 0)
	// 	t.
}

void	put_forks(int id, t_everyone *t)
{
	pthread_mutex_unlock(&t->forks[id]);
	pthread_mutex_unlock(&t->forks[(id + 1) % t->num_philo]);
}

void	xsleep(int id, t_everyone *t)
{
	ft_write(id, t, "is sleeping!");
	while ((get_time() - t->philo[id]->time_last_meal) < t->time_to_sleep)
		continue ;
}

int	ft_check_death(t_one *o)
{
	int i;

	i = 0;
	// while (o->t->philo[i])
	// {

		// printf("%s, %lld\n", "last meal", get_time() - t->time_last_meal);
		// printf(" %s, %lld\n","to die",  get_time() -  t->time_to_die );
		// usleep(1);

		// printf(" time death, %lld, %lld, %ld\n", get_time(), o->time_last_meal, o->t->time_to_die);
		// usleep(10);
		if (get_time() - o->t->start >= (o->time_last_meal  - o->t->start) + o->t->time_to_die)
		{
			// printf(" time death, %lld, %lld, %ld\n", get_time() - o->t->start, o->time_last_meal  - o->t->start, o->t->time_to_die);
			o->t->end = 1;
			o->t->i = i;
			return(1);
		}
	// 	i++;
	// }
	return(0);
}

void	init_philo(t_everyone *t)
{
	int	i;

	i = 0;
	while (i < t->num_philo)
	{
		t->philo[i]->time_last_meal = get_time();
		if (i % 2 == 0)
			usleep(10000);
		pthread_create(&t->philo[i]->thread, NULL, routine, (void *)t->philo[i]);
		// ft_check_death(*t->philo);
		i++;
	}
	while (!t->end)
		continue ;
}

void	change_state(t_one *o)
{
	if (!ft_check_death(o))
	{
		// if (o->id == 0)
			// printf("%d\n", o->philo_status);
		if (o->philo_status == 0)
		{
			if (pthread_mutex_lock(&o->t->forks[o->id]) == 0)
			{
				ft_write(o->id, o->t, "has taken a fork");
				o->philo_status = 1;
			}
		}
		else if(o->philo_status == 1)
		{
			if (pthread_mutex_lock(&o->t->forks[(o->id + 1) % o->t->num_philo]) == 0)
			{
				ft_write(o->id, o->t, "has taken a fork");
				o->t->time = get_time();
				o->philo_status = 2;
			}
			else
			{
				printf("unlock\n");
				pthread_mutex_unlock(&o->t->forks[o->id]);
				o->philo_status = 0;
			}
		}
		else if (o->philo_status == 2)
		{
			ft_write(o->id, o->t, "is eating");
			o->philo_status = 3;
		}
		if (o->philo_status == 3 && get_time() - o->t->time >= o->time_to_eat)
		{
			pthread_mutex_unlock(&o->t->forks[o->id]);
			pthread_mutex_unlock(&o->t->forks[(o->id + 1) % o->t->num_philo]);
			o->philo_status = 4;
			o->t->time = get_time();
			// printf("qui %d %lld\n", o->id + 1, get_time() - o->t->start);
			o->time_last_meal = get_time();
		}
		else if (o->philo_status == 4)
		{
			ft_write(o->id, o->t, "is sleeping");
			o->philo_status = 5;
			// usleep(o->t->time_to_sleep * 1000);
		}
		if (o->philo_status == 5 && get_time() - o->t->time >= o->time_to_sleep)
			o->philo_status = 6;
		else if (o->philo_status == 6)
		{
			ft_write(o->id, o->t, "is thinking");
			o->philo_status = 0;
		}
		usleep(100);
	}
}

void	*routine(void *one)
{
	// int		i;
	t_one	*o;
	t_everyone *t;

	// i = 0;
	o = (t_one *)one;
	t = o->t;
	while (!o->t->end)
	{
		change_state(o);
	}
	ft_write(o->id, t, "died");
	return (NULL);
}
