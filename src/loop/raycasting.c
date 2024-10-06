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

void    handle_vision(t_data *data, t_img *img)
{
    draw_line(data, img, (int)data->player->x * data->win->chunk_size, (int)data->player->y * data->win->chunk_size, 0, 0, 0x000000);
}
