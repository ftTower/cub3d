#include "cub3d.h"

void draw_line(t_data *data, t_img *img, int x0, int y0, int x1, int y1, int color) {
    int dx = abs(x1 - x0); // Différence en x
    int dy = abs(y1 - y0); // Différence en y
    int sx = (x0 < x1) ? 1 : -1; // Direction en x
    int sy = (y0 < y1) ? 1 : -1; // Direction en y
    int err = dx - dy; // Erreur initiale

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

void handle_vision(t_data *data, t_img *img)
{
    float ray_x;
    float ray_y;
    float nb_rays = data->config->r_w / FOV;
    float angle_step = FOV / nb_rays; 
    float start_angle = data->player->angle - (FOV / 2); 

    float max_ray_length = 100;

    for (int i = 0; i < nb_rays; i++)
    {
        float end_x, end_y;
        float ray_len = 0;
        
        while (1)
        {
            float current_angle = start_angle + i * angle_step;
            float angle_rad = current_angle * (M_PI / 180.0);

            
            ray_x = sin(angle_rad) * ray_len; 
            ray_y = cos(angle_rad) * ray_len; 

           
            end_x = data->player->x + ray_x;
            end_y = data->player->y + ray_y;

           
            int map_x = (int)(end_x / (float)data->win->chunk_size);
            int map_y = (int)(end_y / (float)data->win->chunk_size);

            if (map_x < 0 || map_x >= data->map->l || map_y < 0 || map_y >= data->map->h)
                break;
            printf("len %f [x:%d][y:%d] chunktype : %d - [%f %f]\n",ray_len ,map_x, map_y, data->map->chunks[map_x][map_y].type, end_x, end_y);
            if (data->map->chunks[map_x][map_y].type == CHUNK_WALL)
                break;
            ray_len += 1;
            if (ray_len > max_ray_length)
                break;

        }
        draw_line(data, img,
            data->player->x * data->win->chunk_size, 
            data->player->y * data->win->chunk_size, 
            end_x * data->win->chunk_size, 
            end_y * data->win->chunk_size, 
            0x000000);
    }
}





