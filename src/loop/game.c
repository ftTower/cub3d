#include "cub3d.h"

int    loop(t_data *data)
{
    img_refresh(data);
    update_player(data);
    return (0);
}

int    game(t_data * data)
{
    mlx_hook(data->win->win_ptr, 2, 1L<<0, key_press, data);  // KeyPress
    mlx_hook(data->win->win_ptr, 3, 1L<<1, key_release, data);

    mlx_loop_hook(data->win->mlx_ptr, loop, data);
    mlx_loop(data->win->mlx_ptr);
    return (0);
}