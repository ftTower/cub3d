#include "cub3d.h"

void    img_put_key(t_data *data, int w, int h)
{
    if (data->win->keys[KEY_UP])
        mlx_string_put(data->win->mlx_ptr, data->win->win_ptr, w + 7, h , 0x00FF37, "UP");
    else
        mlx_string_put(data->win->mlx_ptr, data->win->win_ptr, w + 7, h , 0xFF0000, "UP");
    if (data->win->keys[KEY_DOWN])
        mlx_string_put(data->win->mlx_ptr, data->win->win_ptr, w, h + 10, 0x00FF37, "DOWN");
    else
        mlx_string_put(data->win->mlx_ptr, data->win->win_ptr, w, h + 10, 0xFF0000, "DOWN");
    if (data->win->keys[KEY_LEFT])
        mlx_string_put(data->win->mlx_ptr, data->win->win_ptr, w - 25, h + 10, 0x00FF37, "LEFT");
    else
        mlx_string_put(data->win->mlx_ptr, data->win->win_ptr, w  - 25, h + 10, 0xFF0000, "LEFT");
    if (data->win->keys[KEY_RIGHT])
        mlx_string_put(data->win->mlx_ptr, data->win->win_ptr, w + 25, h + 10, 0x00FF37, "RIGHT");
    else
        mlx_string_put(data->win->mlx_ptr, data->win->win_ptr, w + 25, h + 10, 0xFF0000, "RIGHT");
}

void    img_put_num(t_data *data, ssize_t w, ssize_t h, ssize_t num)
{
    char *buf;

    buf = ft_itoa((int)num);
    mlx_string_put(data->win->mlx_ptr, data->win->win_ptr, w, h , 0xFFFFFF, buf);
    t_free(buf);
}

void    img_put_player(t_data *data, ssize_t w, ssize_t h)
{
    mlx_string_put(data->win->mlx_ptr, data->win->win_ptr, w + 15 , h , 0xFFFFFF, "player data : ");
    mlx_string_put(data->win->mlx_ptr, data->win->win_ptr, w  , h + 20 , 0xFFFFFF, "player x : ");
    img_put_num(data, w + 100, h + 20, (int)data->player->x);
    mlx_string_put(data->win->mlx_ptr, data->win->win_ptr, w , h + 30, 0xFFFFFF, "player y : ");
    img_put_num(data, w + 100, h + 30, (int)data->player->y);
    mlx_string_put(data->win->mlx_ptr, data->win->win_ptr, w , h + 40, 0xFFFFFF, "player angle : ");
    img_put_num(data, w + 100, h + 40, (int)data->player->angle);
}

void    img_put_map(t_data *data, ssize_t w, ssize_t h)
{
    mlx_string_put(data->win->mlx_ptr, data->win->win_ptr, w + 15 , h , 0xFFFFFF, "map data : ");
    mlx_string_put(data->win->mlx_ptr, data->win->win_ptr, w  , h + 20 , 0xFFFFFF, "map h : ");
    img_put_num(data, w + 100, h + 20, data->map->h);
    mlx_string_put(data->win->mlx_ptr, data->win->win_ptr, w , h + 30, 0xFFFFFF, "map l : ");
    img_put_num(data, w + 100, h + 30, data->map->l);
    if (data->win->map_view)
        mlx_string_put(data->win->mlx_ptr, data->win->win_ptr, w , h + 40, 0xFFFFFF, "map view");
    else
        mlx_string_put(data->win->mlx_ptr, data->win->win_ptr, w , h + 40, 0xFFFFFF, "fpv view");
}

void    img_put_stat(t_data *data)
{

    mlx_string_put(data->win->mlx_ptr, data->win->win_ptr, data->config->r_w - 200, 10 , 0xFFFFFF, "DATA");

    img_put_key(data, data->config->r_w - 150, 30);
    img_put_player(data, data->config->r_w - 200, 90);
    img_put_map(data, data->config->r_w - 200, 150);

    mlx_string_put(data->win->mlx_ptr, data->win->win_ptr, data->config->r_w - 100, data->config->r_h - 10 , 0xFFFFFF, "chunk size x");
    img_put_num(data, data->config->r_w - 28, data->config->r_h - 10, data->win->chunk_size);
}