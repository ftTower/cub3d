/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:08:01 by marvin            #+#    #+#             */
/*   Updated: 2024/11/19 21:47:26 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	update_player(t_data *data)
{
	if (data->win->keys[KEY_UP] && (int)(data->player->y) >= 0
		&& data->map->chunks[(int)(data->player->y
			- 0.3)][(int)(data->player->x)].type != CHUNK_WALL)
		data->player->y -= 0.08;
	if (data->win->keys[KEY_DOWN] && (int)(data->player->y) < data->map->h
		&& data->map->chunks[(int)(data->player->y
			+ 0.3)][(int)(data->player->x)].type != CHUNK_WALL)
		data->player->y += 0.08;
	if (data->win->keys[KEY_LEFT] && (int)(data->player->x) >= 0
		&& data->map->chunks[(int)(data->player->y)][(int)(data->player->x
			- 0.3)].type != CHUNK_WALL)
		data->player->x -= 0.08;
	if (data->win->keys[KEY_RIGHT] && (int)(data->player->x) < data->map->l
		&& data->map->chunks[(int)(data->player->y)][(int)(data->player->x
			+ 0.3)].type != CHUNK_WALL)
		data->player->x += 0.08;
	if (data->win->keys[KEY_ARROW_LEFT])
		data->player->angle -= 2.0;
	if (data->win->keys[KEY_ARROW_RIGHT])
		data->player->angle += 2.0;
}

void	key_press2(int keycode, t_data *data)
{
	if (keycode == 109)
	{
		if (!data->win->map_view)
			data->win->map_view = true;
		else
			data->win->map_view = false;
	}
	if (keycode == 65451)
	{
		data->win->keys[KEY_PLUS] = true;
		if (data->win->map_view && data->win->chunk_size < 400)
			data->win->chunk_size += 2;
		else if (!data->win->map_view && data->player->fov < 160.0f)
			data->player->fov += 2;
	}
	if (keycode == 65453)
	{
		data->win->keys[KEY_MINUS] = true;
		if (data->win->map_view && data->win->chunk_size > 0)
			data->win->chunk_size -= 2;
		else if (!data->win->map_view && data->player->fov > 30.0f)
			data->player->fov -= 2;
	}
}

int	key_press(int keycode, t_data *data)
{
	if (keycode == 13 || keycode == 126 || keycode == 119)
		data->win->keys[KEY_UP] = true;
	if (keycode == 1 || keycode == 125 || keycode == 115)
		data->win->keys[KEY_DOWN] = true;
	if (keycode == 0 || keycode == 123 || keycode == 97)
		data->win->keys[KEY_LEFT] = true;
	if (keycode == 2 || keycode == 124 || keycode == 100)
		data->win->keys[KEY_RIGHT] = true;
	if (keycode == 65361)
		data->win->keys[KEY_ARROW_LEFT] = true;
	if (keycode == 65363)
		data->win->keys[KEY_ARROW_RIGHT] = true;
	if (keycode == 65472 || keycode == 269025098)
	{
		if (!data->win->debug_view)
			data->win->debug_view = true;
		else
			data->win->debug_view = false;
	}
	key_press2(keycode, data);
	if (keycode == 53 || keycode == 65307)
		data_destructor(data);
	return (img_refresh(data), 0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == 13 || keycode == 126 || keycode == 119)
		data->win->keys[KEY_UP] = false;
	else if (keycode == 1 || keycode == 125 || keycode == 115)
		data->win->keys[KEY_DOWN] = false;
	else if (keycode == 0 || keycode == 123 || keycode == 97)
		data->win->keys[KEY_LEFT] = false;
	else if (keycode == 2 || keycode == 124 || keycode == 100)
		data->win->keys[KEY_RIGHT] = false;
	else if (keycode == 65451)
		data->win->keys[KEY_PLUS] = false;
	else if (keycode == 65307)
		data->win->keys[KEY_MINUS] = false;
	if (keycode == 65361)
		data->win->keys[KEY_ARROW_LEFT] = false;
	if (keycode == 65363)
		data->win->keys[KEY_ARROW_RIGHT] = false;
	return (0);
}
