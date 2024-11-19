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

t_file	*get_texture(t_data *data, t_dir dir)
{
	if (dir == DIR_EAST)
		return (data->config->EA);
	else if (dir == DIR_WEAST)
		return (data->config->WE);
	else if (dir == DIR_NORTH)
		return (data->config->NO);
	else
		return (data->config->SO);
}

void	drunk_mode(t_data *data)
{
	if (data->player->fov >= 160.0f)
		data->player->fov = 60.0f;
	data->player->fov += 0.5f;
}

t_ray	*ray_new(t_player *player)
{
	t_ray	*new;

	new = malloc(sizeof(t_ray));
	new->cur_angle = -player->fov / 2;
	new->angle_incr = 0;
	new->w_line = 0;
	new->cur_dist = 0;
	new->start = 0;
	new->end = 0;
	new->wall_height = 0;
	return (new);
}
