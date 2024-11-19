/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:08:01 by marvin            #+#    #+#             */
/*   Updated: 2024/11/19 21:33:47 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t'
		|| c == '\v');
}

ssize_t	ft_atoi(const char *str)
{
	size_t		i;
	ssize_t		sign;
	ssize_t		num;

	i = 0;
	sign = 1;
	num = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	while (str[i] >= '0' && str[i] <= '9')
		num = (num * 10) + (str[i++] - '0');
	return (num * sign);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*ptr_dst;

	if (dst == src)
		return (dst);
	ptr_dst = (unsigned char *)dst;
	while (n--)
		*ptr_dst++ = *(unsigned char *)src++;
	return (dst);
}

bool	identify_starting_angle(t_data *data, char *map)
{
	ssize_t	index;
	bool	checker;

	checker = false;
	index = -1;
	while (map[++index])
	{
		if (map[index] == 'N' || map[index] == 'S' || map[index] == 'E'
			|| map[index] == 'W')
		{
			if (checker)
				return (true);
			checker = true;
		}
		if (map[index] == 'N')
			data->player->angle = 270.0f;
		else if (map[index] == 'S')
			data->player->angle = 90.0f;
		else if (map[index] == 'W')
			data->player->angle = 180.0f;
		else if (map[index] == 'E')
			data->player->angle = 0.0f;
	}
	return (false);
}
