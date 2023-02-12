/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccolaiac <ccolaiac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 19:40:04 by ccolaiac          #+#    #+#             */
/*   Updated: 2023/01/28 18:05:06 by ccolaiac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 48 && str[i] <= 57)
			i++;
		else
			return (FALSE);
	}
	return (TRUE);
}

int	ft_atoi(const char *str)
{
	size_t	c;
	int		s;
	int		res;

	c = 0;
	s = 1;
	res = 0;
	while ((str[c] >= 9 && str[c] <= 13) || str[c] == 32)
		c++;
	if (str[c] == '+' || str[c] == '-')
	{
		if (str[c] == '-')
			s *= -1;
		c++;
	}
	while (str[c] >= '0' && str[c] <= '9')
	{
		res = (str[c] - '0') + (res * 10);
		c++;
	}
	return (res * s);
}

int	check_inputs(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
	{
		if (!(ft_isdigit(argv[1])) && !(ft_atoi(argv[1]) < 0))
			return (FALSE);
		if (!(ft_isdigit(argv[2])) && !(ft_atoi(argv[2]) < 0))
			return (FALSE);
		if (!(ft_isdigit(argv[3])) && !(ft_atoi(argv[3]) < 0))
			return (FALSE);
		if (!(ft_isdigit(argv[4])) && !(ft_atoi(argv[4]) < 0))
			return (FALSE);
		if (argc == 6)
		{
			if (!(ft_isdigit(argv[5])) && !(ft_atoi(argv[5]) < 0))
				return (FALSE);
		}
		return (TRUE);
	}
	return (FALSE);
}