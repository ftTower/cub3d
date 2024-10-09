#include "cub3d.h"

// bool check_open_map(t_map *map)
// {
//     ssize_t h = map->h;
//     ssize_t l = map->l;
    
//     while(l > 0)
//         if (map->chunks[0][l] && ma)
// }

void full_fill(t_map *map, ssize_t h, ssize_t l)
{
    if (h < 0 || l < 0 || h >= map->h || l >= map->l || map->chunks[h][l].type != CHUNK_VOID)
    {
        printf("stopped on h %ld l %ld\n", h, l);
        return;
    }
    
    map->chunks[h][l].type = CHUNK_EMPTY;
    full_fill(map, h - 1, l);
    full_fill(map, h + 1, l);
    full_fill(map, h, l - 1);
    full_fill(map, h, l + 1);
}


bool    fill_check(t_data *data)
{
    ssize_t h;
    ssize_t l;

    
    h = -1;
    printf("l%ld h%ld\n", data->map->l, data->map->h);
    while(++h < data->map->h)
    {
        l = -1;
        while(++l < data->map->l)
            if (data->map->chunks[h][l].type == CHUNK_PLAYER)
            {
                data->player->x = (l + 0.5);
                data->player->y = (h + 0.5);
                full_fill(data->map, h, l);
                data->map->chunks[h][l].type = CHUNK_PLAYER;
                print_chunks(data->map);
                print_checkpoint("PARSE", true, true);
                return false;
            }
    }
    return (print_checkpoint("PARSE", false, true), true);
}
