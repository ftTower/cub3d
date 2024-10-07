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

void calculate_end_ray(t_data *data, float *end_x, float *end_y, float *angle, float angle_incr ,float cur_dist)
{
    *angle = (data->player->angle + angle_incr) * M_PI / 180.0;
    *end_x = data->player->x + cur_dist * cos(*angle);
    *end_y = data->player->y + cur_dist * sin(*angle);
}

void draw_ray_by_angle(t_data *data, t_img *img, float angle_incr)
{
    float end_x;
    float end_y;
    float cur_dist;
    float angle;

    cur_dist = 0.0f;
    while(1)
    {
        calculate_end_ray(data, &end_x, &end_y, &angle, angle_incr ,cur_dist);
        if (end_x < 0.0f || end_y < 0.0f || end_x > data->config->r_w || end_y > data->config->r_h)
            break;
        
        int i_end_x = end_x;
        int i_end_y = end_y;

        if (data->map->chunks[i_end_y][i_end_x].type == CHUNK_WALL)
            break; 

        cur_dist += 0.1f;
    }
    if (data->win->map_view)
        draw_line(data, img,
            data->player->x * data->win->chunk_size, 
            data->player->y * data->win->chunk_size, 
            end_x * data->win->chunk_size, 
            end_y * data->win->chunk_size, 0xFFFFFF);
}

void handle_vision(t_data *data, t_img *img)
{
    float angle_incr;
    float fov = 60.0f; // Champ de vision total en degrés (à ajuster si nécessaire)
    int nombre_de_rayons = data->config->r_w; // Par exemple, égal à la largeur de la fenêtre

    // Calcul de l'incrémentation de l'angle
    angle_incr = fov / nombre_de_rayons;

    // Boucle unique pour balayer tout le champ de vision (de -FOV/2 à +FOV/2)
    float current_angle = -fov / 2; // On commence à -FOV/2
    while (current_angle <= fov / 2) {
        draw_ray_by_angle(data, img, current_angle);
        current_angle += angle_incr; // Incrémenter par l'angle calculé
    }
}







