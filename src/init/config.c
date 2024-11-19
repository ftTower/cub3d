/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:08:01 by marvin            #+#    #+#             */
/*   Updated: 2024/11/19 21:11:36 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	config_init(t_data *data, char *filepath)
{
	data->config = malloc(sizeof(t_config));
	if (!data->config)
		return (print_checkpoint("CONFIG", false, true), true);
	data->config->map = t_file_get(filepath, STATUT_READ);
	if (!data->config->map || rgb_init(t_file_get_patern(data->config->map,
				"C"), &data->config->c_r, &data->config->c_g,
			&data->config->c_b) || rgb_init(t_file_get_patern(data->config->map,
				"F"), &data->config->f_r, &data->config->f_g,
			&data->config->f_b) || res_init(t_file_get_patern(data->config->map,
				"R"), &data->config->r_w, &data->config->r_h))
		return (print_checkpoint("CONFIG", false, true), true);
	return (false);
}

bool	key_init(t_data *data)
{
	data->win->keys = malloc(sizeof(bool) * 10);
	if (!data->win->keys)
		return (true);
	data->win->keys[KEY_UP] = false;
	data->win->keys[KEY_DOWN] = false;
	data->win->keys[KEY_LEFT] = false;
	data->win->keys[KEY_RIGHT] = false;
	data->win->keys[KEY_PLUS] = false;
	data->win->keys[KEY_MINUS] = false;
	data->win->keys[KEY_ARROW_LEFT] = false;
	data->win->keys[KEY_ARROW_RIGHT] = false;
	data->win->keys[KEY_VIEW_SWITCH] = false;
	data->win->keys[KEY_DEBUG_SWITCH] = false;
	return (false);
}

bool	win_init(t_data *data)
{
	data->win = malloc(sizeof(t_win));
	if (!data->win || key_init(data))
		return (true);
	data->win->mlx_ptr = mlx_init();
	data->win->win_ptr = mlx_new_window(data->win->mlx_ptr, data->config->r_w,
			data->config->r_h, "CUB3D");
	return (data->win->map_view = false, data->win->debug_view = false,
		data->win->chunk_size = 20, false);
}

bool	player_init(t_data *data)
{
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		return (true);
	data->player->x = 0;
	data->player->y = 0;
	if (identify_starting_angle(data, data->map->origin))
		return (true);
	data->player->fov = 60.0f;
	return (false);
}

bool	data_init(t_data *data, char *filepath)
{
	data->map = NULL;
	data->config = NULL;
	data->player = NULL;
	data->win = NULL;
	if (config_init(data, filepath) || win_init(data) || texture_init(data)
		|| map_init(data) || player_init(data) || fill_check(data))
		return (print_checkpoint("DATA", false, true), true);
	return (print_config(data->config), false);
}
