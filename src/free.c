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

void config_destructor(t_config *config)
{
    return (t_free(config->NO), t_free(config->SO),\
            t_free(config->WE), t_free(config->EA),  \
            t_file_del(config->map),\
            free(config));
}

void chunks_destructor(t_chunk **chunks, ssize_t h)
{
    while(--h >= 0)
        free(chunks[h]);
    free(chunks);
}

void map_destructor(t_map *map)
{
    return (chunks_destructor(map->chunks, map->h),t_free(map));   
}

void data_destructor(t_data *data)
{
    config_destructor(data->config);
    map_destructor(data->map);
}