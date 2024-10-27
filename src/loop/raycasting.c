#include "cub3d.h"

void draw_line(t_data *data, t_img *img, int x0, int y0, int x1, int y1, int color) {
    int dx = abs(x1 - x0); 
    int dy = abs(y1 - y0); 
    int sx = (x0 < x1) ? 1 : -1; 
    int sy = (y0 < y1) ? 1 : -1; 
    int err = dx - dy;

    while (1) {
        my_mlx_pixel_put(img, x0 + data->win->offset_x, y0 + data->win->offset_y, color);
        if (x0 == x1 && y0 == y1) break;
        int err2 = err * 2;
        if (err2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (err2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void calculate_end_ray(t_data *data, float *end_x, float *end_y, float *angle, float angle_incr ,float cur_dist)
{
    *angle = (data->player->angle + angle_incr) * M_PI / 180.0;
    *end_x = data->player->x + cur_dist * cos(*angle);
    *end_y = data->player->y + cur_dist * sin(*angle);
}

void draw_ray_by_angle(t_data *data, t_img *img, float angle_incr, float *cur_dist)
{
    float end_x;
    float end_y;
    float angle;

    *cur_dist = 0.0f;
    while(1)
    {
        calculate_end_ray(data, &end_x, &end_y, &angle, angle_incr ,*cur_dist);
        if (end_x < 0.0f || end_y < 0.0f || end_x > data->config->r_w || end_y > data->config->r_h)
            break;
        
        int i_end_x = end_x;
        int i_end_y = end_y;

        if (data->map->chunks[i_end_y][i_end_x].type == CHUNK_WALL)
            break; 

        *cur_dist += 0.01f;
    }
    if (data->win->map_view)
        draw_line(data, img,
            data->player->x * data->win->chunk_size, 
            data->player->y * data->win->chunk_size, 
            end_x * data->win->chunk_size, 
            end_y * data->win->chunk_size, 0xFFFFFF);
}

int rgb_to_hex(int r, int g, int b) {
    return (r << 16) + (g << 8) + b;
}

t_raycast *raycast_new(void)
{
    t_raycast *new;

    new = malloc(sizeof(new));
    new->cur_angle = -FOV / 2;
    new->w_line = 0;

    new->cur_dist = 0;
    new->start = 0;
    new->end = 0;
    new->wall_height = 0;
    return (new);
}  

void handle_vision(t_data *data, t_img *img)
{
    float angle_incr;

    t_raycast *r_c;

    r_c = raycast_new();
    angle_incr = data->player->fov / data->config->r_w;
    
    while (r_c->cur_angle <= data->player->fov / 2) //! r_c.current_angle
    {
        draw_ray_by_angle(data, img, r_c->cur_angle, &r_c->cur_dist);
        
        r_c->wall_height = (data->config->r_h / (r_c->cur_dist * cosf(r_c->cur_angle * (M_PI / 180))));
        r_c->start = (data->config->r_h / 2) - (r_c->wall_height / 2);
        r_c->end = r_c->start + r_c->wall_height;
        
        if (!data->win->map_view)
        {
            draw_line(data, img, r_c->w_line - data->win->offset_x, 0 - data->win->offset_y, r_c->w_line - data->win->offset_x, r_c->start - data->win->offset_y, rgb_to_hex(data->config->c_r, data->config->c_g,data->config->c_b));
            draw_line(data, img, r_c->w_line - data->win->offset_x, r_c->start - data->win->offset_y, r_c->w_line - data->win->offset_x, r_c->end - data->win->offset_y, 0x515251);
            draw_line(data, img, r_c->w_line - data->win->offset_x, r_c->end - data->win->offset_y, r_c->w_line - data->win->offset_x, data->config->r_h, rgb_to_hex(data->config->f_r, data->config->f_g,data->config->f_b));
        }
        
        r_c->cur_angle += angle_incr; 
        r_c->w_line++;
    }
    free(r_c);
}








