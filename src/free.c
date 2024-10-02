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

void data_destructor(t_data *data)
{
    config_destructor(data->config);
}