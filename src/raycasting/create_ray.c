#include "cub3d.h"

t_ray	*ray_new(t_player *player)
{
	t_ray	*new;

	new = malloc(sizeof(t_ray));
	new->cur_angle = -player->fov / 2;
	new->w_line = 0;
	new->cur_dist = 0;
	new->start = 0;
	new->end = 0;
	new->wall_height = 0;
	return (new);
}

void	calculate_end_ray(t_data *data, float *end_x, float *end_y,
		float *angle, float angle_incr, float cur_dist)
{
	*angle = (data->player->angle + angle_incr) * M_PI / 180.0;
	*end_x = data->player->x + cur_dist * cos(*angle);
	*end_y = data->player->y + cur_dist * sin(*angle);
}

t_dir	draw_ray_by_angle(t_data *data, t_img *img, float angle_incr,
		float *cur_dist)
{
	float	end_x;
	float	end_y;
	float	angle;
	int		i_end_x;
	int		i_end_y;

	*cur_dist = 0.0f;
	while (1)
	{
		calculate_end_ray(data, &end_x, &end_y, &angle, angle_incr, *cur_dist);
		if (end_x < 0.0f || end_y < 0.0f || end_x > data->config->r_w
			|| end_y > data->config->r_h)
			break ;
		i_end_x = end_x;
		i_end_y = end_y;
		if (data->map->chunks[i_end_y][i_end_x].type == CHUNK_WALL)
			break ;
		*cur_dist += 0.1f;
	}
	if (data->win->map_view)
	{
		draw_line(data, img, data->player->x * data->win->chunk_size,
			data->player->y * data->win->chunk_size, end_x
			* data->win->chunk_size, end_y * data->win->chunk_size, 0xFFFFFF);
		my_mlx_pixel_put(img, (end_x * data->win->chunk_size) + data->win->offset_x,  (end_y * data->win->chunk_size) + data->win->offset_y, 0xF5B932);
	}
	return (DIR_NORTH);
}