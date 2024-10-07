#include "cub3d.h"

t_img    *img_new(t_data *data)
{
    t_img *new;

    new = malloc(sizeof(t_img));
    if (!new)
        return (NULL);
    new->img = mlx_new_image(data->win->mlx_ptr, data->config->r_w, data->config->r_h);
    if (!new->img)
        return (NULL);
    new->addr = mlx_get_data_addr(new->img, &new->bits_per_pixel, &new->line_length, &new->endian);
    if (!new->addr)
        return (NULL);
    new->width = data->config->r_w;
    new->height = data->config->r_h;
    return (new);
}

void      img_destructor(t_win *win,t_img *img)
{
    if (img && img->img)
        mlx_destroy_image(win->mlx_ptr, img->img);
    t_free(img);
}

void    img_null_pixel(t_data *data, t_img *img)
{
    ssize_t h;
    ssize_t w;

    h = -1;
    while(++h < data->config->r_h)
    {
        w = -1;
        while(++w < data->config->r_w)
            my_mlx_pixel_put(img, w, h, 0x000000);
    }
}

void    img_refresh(t_data *data)
{
    t_img *img;

    img = img_new(data);
    img_draw(data, img);
    mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr, img->img, 0, 0);
    img_put_stat(data);
    mlx_destroy_image(data->win->mlx_ptr, img->img);
    t_free(img);
}
