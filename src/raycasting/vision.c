#include "cub3d.h"

void	handle_vision(t_data *data, t_img *img)
{
	t_ray	*r_c;

	r_c = ray_new(data->player);
	r_c->angle_incr = data->player->fov / data->config->r_w;
	if (data->win->map_view)
			img_draw_map(data, img);
	while (r_c->cur_angle <= data->player->fov / 2) //! r_c.current_angle
	{
		r_c->direction = get_ray_dist(data, img, r_c);
		if (!data->win->map_view)
		{
			if (r_c->cur_dist != 0)
				r_c->wall_height = (data->config->r_h / (r_c->cur_dist
							* cosf(r_c->cur_angle * (M_PI / 180))));
			else
				r_c->wall_height = data->config->r_h;
			r_c->start = (data->config->r_h / 2) - (r_c->wall_height / 2);
			r_c->end = r_c->start + r_c->wall_height;
			vertical_draw(data, img, r_c, DRAW_CELL);
			vertical_draw(data, img, r_c, DRAW_WALL);
			vertical_draw(data, img, r_c, DRAW_FLOOR);
		}
		r_c->cur_angle += r_c->angle_incr;
		r_c->w_line++;
	}
	free(r_c);
}