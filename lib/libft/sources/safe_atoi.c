/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlitvino <mlitvino@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:13:05 by mlitvino          #+#    #+#             */
/*   Updated: 2025/04/23 17:13:24 by mlitvino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	safe_atoi(const char *str)
{
		long long	res;
		long long	sign;

	res = 0;
	sign = 1;
	if (str == NULL)
		return (0);
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign *= -1;
	   if (!(*str >= '0' && *str <= '9'))
		   return (((long long)INT_MAX) + 1LL);
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str++ - '0');
		   if (res > INT_MAX || res < INT_MIN)
			   return (((long long)INT_MAX) + 1LL);
	}
	while (ft_isspace(*str))
		str++;
	   if (*str)
		   return (((long long)INT_MAX) + 1LL);
		return (res * sign);
}
