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

void    my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
    char    *dst;

    if (x >= 0 && x < img->width && y >= 0 && y < img->height)
    {
        dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
        *(unsigned int*)dst = color;
    }
}

void img_draw_chunk(t_data *data, t_img *img, ssize_t h, ssize_t w)
{
    ssize_t h_c;
    ssize_t w_c;

    ssize_t start_h = h * data->win->chunk_size;
    ssize_t start_w = w * data->win->chunk_size;

    for (h_c = start_h; h_c < start_h + data->win->chunk_size; h_c++)
    {
        for (w_c = start_w; w_c < start_w + data->win->chunk_size; w_c++)
        {
            if (h_c >= 0 && h_c < img->height && w_c >= 0 && w_c < img->width)
            {
                if (data->map->chunks[h][w].type == CHUNK_EMPTY || data->map->chunks[h][w].type == CHUNK_PLAYER)
                    my_mlx_pixel_put(img, w_c, h_c, 0x49998E); // Couleur pour CHUNK_EMPTY et CHUNK_PLAYER
                else if (data->map->chunks[h][w].type == CHUNK_WALL)
                    my_mlx_pixel_put(img, w_c, h_c, 0x1D2DBF); // Couleur pour CHUNK_WALL
            }
        }
    }
}


void    img_draw_map(t_data *data, t_img *img)
{
    ssize_t h;
    ssize_t w;

    h = -1;
    while(++h < data->map->h)
    {
        w = -1;
        while(++w < data->map->l)
            img_draw_chunk(data, img, h, w);
    }
}

void    img_draw(t_data *data, t_vision vision, t_img *img)
{
    if (vision == VISION_MAP)
        img_draw_map(data, img);
}

void    img_refresh(t_data *data)
{
    t_img *img;


    img = img_new(data);
    img_draw(data, VISION_MAP, img);
    mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr, img->img, 0, 0);
    mlx_destroy_image(data->win->mlx_ptr, img->img);
    t_free(img);
}

// bool    img_add_back(t_img **display, t_img *img)
// {   
//     t_img *current;

//     if (!*display)
//         return (*display = img, false);
//     current = *display;
//     while(current->next)
//         current = current->next;
//     return (current->next = img, false);
// }
