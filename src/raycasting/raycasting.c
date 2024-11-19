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

void	calculate_end_ray(t_data *data, float *end_x, float *end_y,
	float *angle, float angle_incr, float cur_dist)
{
	*angle = (data->player->angle + angle_incr) * M_PI / 180.0;
	*end_x = data->player->x + cur_dist * cos(*angle);
	*end_y = data->player->y + cur_dist * sin(*angle);
}

void	get_ray_dist(t_data *data, t_img *img, t_ray *r_c)
{
	float	angle;
	int		i_end_x;
	int		i_end_y;

	r_c->cur_dist = 0.0f;
	while (r_c->cur_dist < 50.0f)
	{
		calculate_end_ray(data, &r_c->end_x, &r_c->end_y,
			&angle, r_c->cur_angle, r_c->cur_dist);
		if (r_c->end_x < 0.0f || r_c->end_y < 0.0f
			|| r_c->end_x > data->config->r_w || r_c->end_y > data->config->r_h)
			break ;
		i_end_x = (int)r_c->end_x;
		i_end_y = (int)r_c->end_y;
		if (data->map->chunks[i_end_y][i_end_x].type == CHUNK_WALL)
			break ;
		r_c->cur_dist += 0.01f;
	}
	if (data->win->map_view)
		my_mlx_pixel_put(img, (r_c->end_x * data->win->chunk_size)
			+ data->win->offset_x, (r_c->end_y * data->win->chunk_size)
			+ data->win->offset_y, 0xF5B932);
}

void	get_ray_dir(t_ray *r_c)
{
	if ((r_c->end_x - (int)r_c->end_x) < 0.01f)
		r_c->direction = DIR_WEAST;
	else if ((r_c->end_y - (int)r_c->end_y) < 0.01f)
		r_c->direction = DIR_NORTH;
	else if ((1.0f - (r_c->end_x - (int)r_c->end_x)) < 0.01f)
		r_c->direction = DIR_EAST;
	else if ((1.0f - (r_c->end_y - (int)r_c->end_y)) < 0.01f)
		r_c->direction = DIR_SOUTH;
}

void	handle_pov(t_data *data, t_ray *r_c, t_img *img)
{
	if (r_c->cur_dist != 0)
		r_c->wall_height = (data->config->r_h /
				(r_c->cur_dist * cosf(r_c->cur_angle * (M_PI / 180))));
	else
		r_c->wall_height = data->config->r_h;
	r_c->start = (data->config->r_h / 2) - (r_c->wall_height / 2);
	r_c->end = r_c->start + r_c->wall_height;
	if (!data->win->debug_view)
	{
		vertical_draw(data, img, r_c, DRAW_CELL);
		vertical_draw(data, img, r_c, DRAW_WALL);
		vertical_draw(data, img, r_c, DRAW_FLOOR);
	}
	else
	{
		my_mlx_pixel_put(img, r_c->w_line, r_c->start,
			rgb_to_hex(data->config->c_r, data->config->c_g,
				data->config->c_b));
		my_mlx_pixel_put(img, r_c->w_line, r_c->end,
			rgb_to_hex(data->config->c_r, data->config->c_g,
				data->config->c_b));
	}
}

/*drunk_mode(data);*/
void	handle_raycasting(t_data *data, t_img *img)
{
	t_ray	*r_c;

	r_c = ray_new(data->player);
	r_c->angle_incr = data->player->fov / data->config->r_w;
	if (data->win->map_view)
		img_draw_map(data, img);
	while (r_c->cur_angle <= data->player->fov / 2)
	{
		get_ray_dist(data, img, r_c);
		get_ray_dir(r_c);
		if (!data->win->map_view)
			handle_pov(data, r_c, img);
		r_c->cur_angle += r_c->angle_incr;
		r_c->w_line++;
	}
	free(r_c);
}
