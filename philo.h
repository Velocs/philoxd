/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aliburdi <aliburdi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:40:04 by ccolaiac          #+#    #+#             */
/*   Updated: 2023/02/14 16:31:00 by aliburdi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define TRUE 1
# define FALSE 0

# define EAT "is eating"
# define SLEEP "is sleeping"
# define THINK "is thinking"
# define FORK_LEFT "has taken a left fork"
# define FORK_RIGHT "has taken a right fork"
# define DIED "died"

typedef struct s_one
{
	pthread_t			thread;

	int					id;
	int					num_of_times_ate;
	int					philo_status;
	long long			time_to_eat;
	long long			time_to_sleep;
	long long			time_to_die;
	long long			time_last_meal;
	struct s_everyone	*t;

}					t_one;

typedef struct s_everyone
{
	int				fifth_argument;
	int				num_philo;
	int				*forchette;
	long long		start;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	time_t			time_to_think;
	int				num_of_times_eat;
	int				i;
	int				end;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	long long		time;

	t_one			**philo;

}t_everyone;

int			check_inputs(int argc, char **argv);
int			ft_atoi(const char *str);
int			ft_isdigit(char *str);
long long	get_time(void);
long long	delta_time(long long time);
void		change_state(t_one *o);
void		forchette(t_everyone *t);
void		*routine(void *one);
void		init_fork(t_everyone *t);
void		init_philo(t_everyone *t);
#endif
