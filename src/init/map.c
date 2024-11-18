#include "cub3d.h"

void chunks_null(t_chunk **chunks, ssize_t l, ssize_t h)
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

bool	map_maker(t_map *map, char **raw_map)
{
	ssize_t	h;
	ssize_t	l;
	ssize_t	c_h;
	ssize_t	c_l;

	h = -1;
	c_h = -1;
	map->chunks = chunks_malloc(map->l, map->h);
	if (!map->chunks)
		return (true);
	while (raw_map[++h])
	{
		++c_h;
		c_l = -1;
		l = -1;
		while (raw_map[h][++l])
		{
			if (is_map_char("012NSWE", raw_map[h][l]))
			{
				if (raw_map[h][l] == '0')
					map->chunks[c_h][++c_l].type = CHUNK_VOID;
				else if (raw_map[h][l] == '1')
					map->chunks[c_h][++c_l].type = CHUNK_WALL;
				else if (raw_map[h][l] == 'N' || raw_map[h][l] == 'S'
					|| raw_map[h][l] == 'W' || raw_map[h][l] == 'E')
					map->chunks[c_h][++c_l].type = CHUNK_PLAYER;
			}
		}
	}
	return (t_rfree(raw_map), false);
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
