#include "cub3d.h"

void      img_destructor(t_win *win,t_img *img)
{
    if (img && img->img)
        mlx_destroy_image(win->mlx_ptr, img->img);
    t_free(img);
}

t_img    *img_new(t_data *data)
{
    t_img *new;

    new = malloc(sizeof(t_img));
    if (!new)
        return (NULL);
    new->img = mlx_new_image(data->win->mlx_ptr, data->config->r_w,data->config->r_h);
    if (!new->img)
        return (NULL);
    new->addr = mlx_get_data_addr(new->img, &new->bits_per_pixel, &new->line_length, &new->endian);
    if (!new->addr)
        return (NULL);
    new->width = data->config->r_w;
    new->height = data->config->r_h;
    new->next = NULL;
    return (new);
}