#include "cub3d.h"

int key_press(int keycode, t_data *data)
{
    if (keycode == 13 || keycode == 126 || keycode == 119)
        data->win->keys[KEY_UP] = true;
    else if (keycode == 1 || keycode == 125 || keycode == 115)
        data->win->keys[KEY_DOWN] = true;
    else if (keycode == 0 || keycode == 123 || keycode == 97)
        data->win->keys[KEY_LEFT] = true;
    else if (keycode == 2 || keycode == 124 || keycode == 100)
        data->win->keys[KEY_RIGHT] = true;
    else if (keycode == 65451)
    {
        data->win->keys[KEY_PLUS] = true;
        data->win->chunk_size +=2;   
    }
    else if (keycode == 65453)
    {
        data->win->keys[KEY_MINUS] = true;
        if (data->win->chunk_size > 0)
            data->win->chunk_size -=2;
    }
    else if (keycode == 53 || keycode == 65307)
        data_destructor(data);
    return (img_refresh(data),0);
}

int key_release(int keycode, t_data *data)
{
    if (keycode == 13 || keycode == 126 || keycode == 119)
        data->win->keys[KEY_UP] = false;
    else if (keycode == 1 || keycode == 125 || keycode == 115)
        data->win->keys[KEY_DOWN] = false;
    else if (keycode == 0 || keycode == 123 || keycode == 97)
        data->win->keys[KEY_LEFT] = false;
    else if (keycode == 2 || keycode == 124 || keycode == 100)
        data->win->keys[KEY_RIGHT] = false;
    else if (keycode == 65451)
        data->win->keys[KEY_PLUS] = false;
    else if (keycode == 65307)
        data->win->keys[KEY_MINUS] = false;
    return (0);
}