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

void	chunks_null(t_chunk **chunks, ssize_t l, ssize_t h)
{
	ssize_t	index;

	while (--h >= 0)
	{
		index = -1;
		while (++index < l)
			chunks[h][index].type = CHUNK_VOID;
	}
}

t_chunk	**chunks_malloc(ssize_t l, ssize_t h)
{
	ssize_t	index;
	t_chunk	**new;

	new = (t_chunk **)malloc((h + 1) * sizeof(t_chunk *));
	if (!new)
		return (NULL);
	index = -1;
	while (++index < h)
	{
		new[index] = (t_chunk *)malloc((l) * sizeof(t_chunk));
		if (!new[index])
		{
			while (--index >= 0)
				free(new[index]);
			free(new);
			return (NULL);
		}
	}
	new[h] = NULL;
	return (chunks_null(new, l, h), new);
}

bool	map_size(t_map *map, char *map_line)
{
	char	**buf;
	ssize_t	l;
	ssize_t	h;
	ssize_t	index;

	map->chunks = NULL;
	h = -1;
	buf = ft_split(map_line, '\n');
	if (!buf)
		return (free(map_line), true);
	free(map_line);
	while (buf[++h])
	{
		index = -1;
		l = 0;
		while (buf[h][++index])
			if (is_map_char("012NSWE", buf[h][index]))
				l++;
		if (l > map->l)
			map->l = l;
	}
	map->h = h;
	return (map_maker(map, buf));
}

bool	map_init(t_data *data)
{
	char	*map;
	data->map = malloc(sizeof(t_map));
	if (!data->map)
		return (print_checkpoint("MAP", false, false), true);
	data->map->l = -1;
	data->map->h = -1;
	map = t_file_get_map(data->config->map, "012NSEW \n");
	return (map_size(data->map, map));
}
