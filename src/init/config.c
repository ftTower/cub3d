#include "cub3d.h"

bool    texture_init(t_data *data)
{
    t_file *buf;

    data->config->EA = path_format(t_file_get_patern(data->config->map, "EA"));
    data->config->WE = path_format(t_file_get_patern(data->config->map, "WE"));
    data->config->NO = path_format(t_file_get_patern(data->config->map, "NO"));
    data->config->SO = path_format(t_file_get_patern(data->config->map, "SO"));    
    if (!data->config->EA || !data->config->WE || !data->config->NO ||\
        !data->config->SO)
        return (print_checkpoint("TEXTURE", false, false),true);
    buf = t_file_get(data->config->EA, STATUT_READ);
    if (!buf)
        return (print_checkpoint("TEXTURE", false, false),true);
    t_file_del(buf);
    buf = t_file_get(data->config->WE, STATUT_READ);
    if (!buf)
        return (print_checkpoint("TEXTURE", false, false),true);
    t_file_del(buf);
    buf = t_file_get(data->config->NO, STATUT_READ);
    if (!buf)
        return (print_checkpoint("TEXTURE", false, false),true);
    t_file_del(buf);
    buf = t_file_get(data->config->SO, STATUT_READ);
    if (!buf)
        return (print_checkpoint("TEXTURE", false, false),true);
    return (t_file_del(buf), print_checkpoint("TEXTURE", true, false),false);
}

bool    rgb_init(char *str, ssize_t *r, ssize_t *g, ssize_t *b)
{
    char **buf;

    buf = ft_split(str, ',');
    if (!buf)
        return (free(str), print_checkpoint("RGB", false, false), true);
    *r = 0;
    *g = 0;
    *b = 0;
    if (buf[0])
       *r = ft_atoi(buf[0]);
    if (buf[1])
        *g = ft_atoi(buf[1]);
    if (buf[2])
        *b = ft_atoi(buf[2]);
    return (free(str), t_rfree(buf),print_checkpoint("RGB", true, false),false);
}

bool    res_init(char *str, ssize_t *w, ssize_t *h)
{
 char **buf;

    buf = ft_split(str, ' ');
    if (!buf)
        return (free(str), print_checkpoint("RESOLUTION", false, false), true);
    *w = 0;
    *h = 0;
    if (buf[0])
        *w = ft_atoi(buf[0]);
    if (buf[1])
        *h = ft_atoi(buf[1]);
    return (free(str), t_rfree(buf),print_checkpoint("RESOLUTION", true, false),false);
}

bool    config_init(t_data *data, char *filepath)
{
    data->config = malloc(sizeof(t_config));
    if (!data->config)
        return (print_checkpoint("CONFIG", false, false), true);
    data->config->map = t_file_get(filepath, STATUT_READ);
    if (!data->config->map || texture_init(data) \
        || rgb_init(t_file_get_patern(data->config->map, "C"), &data->config->c_r, &data->config->c_g, &data->config->c_b) \
        || rgb_init(t_file_get_patern(data->config->map, "F"), &data->config->f_r, &data->config->f_g, &data->config->f_b) \
        || res_init(t_file_get_patern(data->config->map, "R"), &data->config->r_w, &data->config->r_h))
        return (print_checkpoint("CONFIG", false, false),true);
    return (print_checkpoint("CONFIG", true, false),false);
}

bool    data_init(t_data *data, char *filepath)
{
    data->config = NULL;
    if (config_init(data, filepath) || map_init(data))
        return (print_checkpoint("DATA", false, true),true);
    return (print_checkpoint("DATA", true, true),print_config(data->config),false);
}
