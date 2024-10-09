#include "cub3d.h"

void t_rfree(char **ptr)
{
    ssize_t index;

    index = -1;
    while(ptr[++index])
        free(ptr[index]);
    if (ptr)
        free(ptr);
}

void t_free(void *ptr)
{
    if (ptr)
        free(ptr);
}

void win_destructor(t_win *win)
{
    if (!win)
        return ;
    if (win->win_ptr)
        mlx_destroy_window(win->mlx_ptr, win->win_ptr);
    if (win->mlx_ptr)
    {
        mlx_destroy_display(win->mlx_ptr);  // S'assure de fermer correctement la connexion au display.
        free(win->mlx_ptr);  // Libérer le pointeur mlx
    }
    t_free(win->keys);
    t_free(win);
}

void config_destructor(t_data *data)
{
    img_destructor(data->win, data->config->NO->img);
    img_destructor(data->win, data->config->SO->img);
    img_destructor(data->win, data->config->WE->img);
    img_destructor(data->win, data->config->EA->img);
    t_file_del(data->config->NO);
    t_file_del(data->config->SO);
    t_file_del(data->config->WE);
    t_file_del(data->config->EA);
    t_file_del(data->config->map);
    free(data->config);
}

void chunks_destructor(t_chunk **chunks, ssize_t h)
{
    if (chunks)
    {
        while(--h >= 0)
            free(chunks[h]);
        free(chunks);
    }
}

void map_destructor(t_map *map)
{
    if (!map)
        return ;
    return (chunks_destructor(map->chunks, map->h),t_free(map));   
}

void data_destructor(t_data *data)
{
    config_destructor(data);
    t_free(data->player);
    map_destructor(data->map);
    win_destructor(data->win);
    exit(0);
}