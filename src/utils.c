/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:08:01 by marvin            #+#    #+#             */
/*   Updated: 2024/06/05 18:08:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*path_format(char *str)
{
	char	*ret;
	char	**buf;

	buf = ft_split(str, ' ');
	if (!buf || !buf[0])
		return (NULL);
	ret = ft_strdup(buf[0]);
	if (!ret)
		return (t_rfree(buf), NULL);
	t_rfree(buf);
	buf = ft_split(ret, '\n');
	if (!buf || !buf[0])
		return (free(ret), NULL);
	free(ret);
	ret = ft_strdup(buf[0]);
	if (!ret)
		return (t_rfree(buf), NULL);
	return (free(str), t_rfree(buf), ret);
}

bool	is_map_char(char *map_chars, char c)
{
	ssize_t	index;

	index = -1;
	while (map_chars[++index])
		if (map_chars[index] == c)
			return (true);
	return (false);
}

static char	*fill(int nb, long int nbr, int size)
{
	char	*str;

	if (nb == 0)
	{
		str = (char *)malloc(sizeof(char) * 2);
		if (!str)
			return (NULL);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	str = (char *)malloc(sizeof(char) * size);
	if (!str)
		return (NULL);
	str[size - 1] = '\0';
	size -= 2;
	while (nbr)
	{
		str[size--] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (size == 0 && nb < 0)
		str[size] = '-';
	return (str);
}

static int	mal_size(int nb, long int nbr, int size)
{
	if (nb < 0)
		size += 2;
	else
		size += 1;
	while (nbr)
	{
		size++;
		nbr /= 10;
	}
	return (size);
}

char	*ft_itoa(int nb)
{
	long int	nbr;

	nbr = nb;
	if (nb < 0)
		nbr *= -1;
	return (fill(nb, nbr, mal_size(nb, nbr, 0)));
}
