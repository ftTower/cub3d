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

void	t_file_destructor(t_data *data, t_file *file)
{
	if (file)
	{
		img_destructor(data->win, file->img);
		t_file_del(file);
	}
}

void	config_destructor(t_data *data)
{
	t_file_destructor(data, data->config->NO);
	t_file_destructor(data, data->config->SO);
	t_file_destructor(data, data->config->EA);
	t_file_destructor(data, data->config->WE);
	t_file_del(data->config->map);
	t_free(data->config);
}

void	chunks_destructor(t_chunk **chunks, ssize_t h)
{
	if (chunks)
	{
		while (--h >= 0)
			free(chunks[h]);
		free(chunks);
	}
}

void	map_destructor(t_map *map)
{
	if (!map)
		return ;
	return (chunks_destructor(map->chunks, map->h), t_free(map));
}

void	data_destructor(t_data *data)
{
	config_destructor(data);
	t_free(data->player);
	map_destructor(data->map);
	win_destructor(data->win);
	exit(0);
}
