#include "cub3d.h"

int	rgb_to_hex(int r, int g, int b)
{
	return ((r << 16) + (g << 8) + b);
}

int	get_color_texture(t_file *texture, int x, int y)
{
	int	color;

	if (x < 0 || x >= texture->img->width || y < 0 || y >= texture->img->height)
		return (0);
	color = *(int *)(texture->img->addr + (y * texture->img->line_length + x
				* (texture->img->bits_per_pixel / 8)));
	return (color);
}

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

void vertical_draw_texture(t_data *data, t_img *img, t_ray *r_c)
{
    float index;
    int   tex_x;
    int   tex_y;
    t_file *texture;

    texture = get_texture(data, r_c->direction);

    // Correction du calcul de tex_x pour les murs est et ouest
    if (r_c->direction == DIR_NORTH || r_c->direction == DIR_SOUTH)
        tex_x = (int)(r_c->end_x * texture->img->width) % texture->img->width;
    else
        tex_x = (int)(r_c->end_y * texture->img->width) % texture->img->width;

    index = r_c->start;
    while (index < r_c->end)
    {
        // Calcul de tex_y en fonction de la hauteur visible
        tex_y = (int)((index - r_c->start) * texture->img->height / (r_c->end - r_c->start));

        if (tex_y < 0 || tex_y >= texture->img->height)
            tex_y = 0;

        my_mlx_pixel_put(img, r_c->w_line, (int)index,
            get_color_texture(texture, tex_x, tex_y));
        index++;
    }
}


void	vertical_draw(t_data *data, t_img *img, t_ray *r_c, t_draw type_code)
{
	float	index;

	if (type_code == DRAW_CELL)
	{
		index = 0;
		while (index++ < r_c->start)
			my_mlx_pixel_put(img, r_c->w_line, index,
				rgb_to_hex(data->config->c_r, data->config->c_g,
					data->config->c_b));
	}
	else if (type_code == DRAW_FLOOR)
	{
		index = r_c->end;
		while (index++ < data->config->r_h)
			my_mlx_pixel_put(img, r_c->w_line, index,
				rgb_to_hex(data->config->f_r, data->config->f_g,
					data->config->f_b));
	}
	else if (type_code == DRAW_WALL)
		vertical_draw_texture(data, img, r_c);
}


