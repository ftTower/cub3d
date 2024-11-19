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

bool	check_open_map(t_map *map)
{
	ssize_t	h;
	ssize_t	l;

	h = 0;
	l = 0;
	while (l < map->l)
		if (map->chunks[0][l++].type == CHUNK_EMPTY)
			return (true);
	while (h < map->h)
		if (map->chunks[h++][l - 1].type == CHUNK_EMPTY)
			return (true);
	while (l > 0)
		if (map->chunks[h - 1][l-- - 1].type == CHUNK_EMPTY)
			return (true);
	while (h > 0)
		if (map->chunks[h-- - 1][0].type == CHUNK_EMPTY)
			return (true);
	return (false);
}

void	full_fill(t_map **map, ssize_t h, ssize_t l)
{
	if ((*map)->chunks[h][l].type != CHUNK_VOID &&
		(*map)->chunks[h][l].type != CHUNK_PLAYER)
		return ;
	(*map)->chunks[h][l].type = CHUNK_EMPTY;
	if (h > 0)
		full_fill(map, h - 1, l);
	if (l > 0)
		full_fill(map, h, l - 1);
	if (h < (*map)->h - 1)
		full_fill(map, h + 1, l);
	if (l < (*map)->l - 1)
		full_fill(map, h, l + 1);
}

bool	fill_check(t_data *data)
{
	ssize_t	h;
	ssize_t	l;

	h = -1;
	while (++h < data->map->h)
	{
		l = -1;
		while (++l < data->map->l)
		{
			if (data->map->chunks[h][l].type == CHUNK_PLAYER)
			{
				data->player->x = (l + 0.5);
				data->player->y = (h + 0.5);
				full_fill(&data->map, h, l);
				if (check_open_map(data->map))
					return (print_checkpoint("PARSE", false, true), true);
				return (false);
			}
		}
	}
	return (print_checkpoint("PARSE", false, true), true);
}

void	map_maker2(ssize_t h, t_map *map, char **raw_map)
{
	ssize_t	l;
	ssize_t	c_h;
	ssize_t	c_l;

	c_h = h;
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

bool	map_maker(t_map *map, char **raw_map)
{
	ssize_t	h;

	h = -1;
	map->chunks = chunks_malloc(map->l, map->h);
	if (!map->chunks)
		return (true);
	while (raw_map[++h])
		map_maker2(h, map, raw_map);
	return (t_rfree(raw_map), false);
}
