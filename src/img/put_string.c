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
    mlx_string_put(data->win->mlx_ptr, data->win->win_ptr, w, h , 0x000000, buf);
    t_free(buf);
}

void    img_put_player(t_data *data, ssize_t w, ssize_t h)
{
    mlx_string_put(data->win->mlx_ptr, data->win->win_ptr, w + 15 , h , 0x000000, "player data : ");
    mlx_string_put(data->win->mlx_ptr, data->win->win_ptr, w  , h + 20 , 0x000000, "player x : ");
    img_put_num(data, w + 100, h + 20, (int)data->player->x);
    mlx_string_put(data->win->mlx_ptr, data->win->win_ptr, w , h + 30, 0x000000, "player y : ");
    img_put_num(data, w + 100, h + 30, (int)data->player->y);
    

    // if ((int)data->player->x < data->map->l && (int)data->player->y < data->map->h &&
    // (int)data->player->x >= 0 && (int)data->player->y >= 0)
    // {
    //     if(data->map->chunks[(int)data->player->x][(int)data->player->y].type == CHUNK_EMPTY)
    //         mlx_string_put(data->win->mlx_ptr, data->win->win_ptr, w , h + 40, 0x000000, "chunk empty");
    //     else if(data->map->chunks[(int)data->player->x][(int)data->player->y].type == CHUNK_WALL)
    //         mlx_string_put(data->win->mlx_ptr, data->win->win_ptr, w , h + 40, 0x000000, "chunk wall");
    //     else if(data->map->chunks[(int)data->player->x][(int)data->player->y].type == CHUNK_VOID)
    //         mlx_string_put(data->win->mlx_ptr, data->win->win_ptr, w , h + 40, 0x000000, "chunk void");
    // }
}

void    img_put_stat(t_data *data)
{

    mlx_string_put(data->win->mlx_ptr, data->win->win_ptr, data->config->r_w - 200, 10 , 0x000000, "DATA");

    img_put_key(data, data->config->r_w - 150, 30);

    mlx_string_put(data->win->mlx_ptr, data->win->win_ptr, data->config->r_w - 200, 70 , 0x000000, "chunk size : ");
    img_put_num(data, data->config->r_w - 100, 70, data->win->chunk_size);

    img_put_player(data, data->config->r_w - 200, 90);
    
}