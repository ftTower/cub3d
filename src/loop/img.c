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
    ssize_t start_h;
    ssize_t start_w;
    int chunk_size;

    chunk_size = data->win->chunk_size;
    start_h = h * chunk_size + data->win->offset_y;
    start_w = w * chunk_size + data->win->offset_x;
    h_c = start_h;

    while (h_c < start_h + chunk_size - 1)
    {
        w_c = start_w;
        while (w_c < start_w + chunk_size - 1)
        {
            if (h_c >= 0 && h_c < img->height && w_c >= 0 && w_c < img->width)
            {
                if (data->map->chunks[h][w].type == CHUNK_EMPTY || data->map->chunks[h][w].type == CHUNK_PLAYER)
                    my_mlx_pixel_put(img, w_c, h_c, 0x0E731D);
                else if (data->map->chunks[h][w].type == CHUNK_WALL)
                    my_mlx_pixel_put(img, w_c, h_c, 0x515251);
            }
            w_c++;
        }
        h_c++;
    }
}

void img_draw_player(t_data *data, t_img *img, int size)
{
    int x;
    int y;
    int start_x;
    int start_y;

    x = (data->player->x * data->win->chunk_size) + data->win->offset_x + (data->win->chunk_size / 2);
    y = (data->player->y * data->win->chunk_size) + data->win->offset_y + (data->win->chunk_size / 2);
    start_y = y - (size / 2);
    while(start_y < (y + 1) + (size / 2))
    {
        start_x = x - (size / 2);
        while(start_x < (x + 1) + (size / 2))
            my_mlx_pixel_put(img, start_x++, start_y, 0xFF0000);
        start_y++;
    }
}

void img_draw_map(t_data *data, t_img *img)
{
    ssize_t h;
    ssize_t w;

    data->win->offset_x = (data->config->r_w - (data->map->l * data->win->chunk_size)) / 2;
    data->win->offset_y = (data->config->r_h - (data->map->h * data->win->chunk_size)) / 2;
    h = -1;
    while (++h < data->map->h)
    {
        w = -1;
        while (++w < data->map->l)
            img_draw_chunk(data, img, h, w);
    }
    img_draw_player(data, img, data->win->chunk_size / 3);
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
            my_mlx_pixel_put(img, w, h, 0xFFFFFF);
    }
}

void    img_draw(t_data *data, t_vision vision, t_img *img)
{
    img_null_pixel(data, img);
    if (vision == VISION_MAP)
        img_draw_map(data, img);
}

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

void    img_put_stat(t_data *data)
{

    mlx_string_put(data->win->mlx_ptr, data->win->win_ptr, data->config->r_w - 200, 10 , 0x000000, "DATA");
    img_put_key(data, data->config->r_w - 150, 30);
    mlx_string_put(data->win->mlx_ptr, data->win->win_ptr, data->config->r_w - 200, 70 , 0x000000, "chunk size : ");
    img_put_num(data, data->config->r_w - 100, 70, data->win->chunk_size);
}

void    img_refresh(t_data *data)
{
    t_img *img;

    img = img_new(data);
    img_draw(data, VISION_MAP, img);
    mlx_put_image_to_window(data->win->mlx_ptr, data->win->win_ptr, img->img, 0, 0);
    img_put_stat(data);
    mlx_destroy_image(data->win->mlx_ptr, img->img);
    t_free(img);
}
