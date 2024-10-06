#include "cub3d.h"

bool    full_fill(t_map *map, ssize_t h, ssize_t l)
{
    map->chunks[h][l].type = CHUNK_EMPTY;
    if (h == 0 || l == 0 || h == map->h  - 1|| l == map->l - 1)
        return (true);
    if (map->chunks[h - 1][l].type == CHUNK_VOID && map->chunks[h - 1][l].type != CHUNK_EMPTY)
        full_fill(map, h - 1, l);
    if (map->chunks[h + 1][l].type == CHUNK_VOID && map->chunks[h + 1][l].type != CHUNK_EMPTY)
        full_fill(map, h + 1, l);
    if (map->chunks[h][l - 1].type == CHUNK_VOID && map->chunks[h][l - 1].type != CHUNK_EMPTY)
        full_fill(map, h, l -1);
    if (map->chunks[h][l + 1].type == CHUNK_VOID && map->chunks[h][l + 1].type != CHUNK_EMPTY)
        full_fill(map, h, l + 1);
    return (false);
}

bool    fill_check(t_data *data)
{
    ssize_t h;
    ssize_t l;

    
    h = -1;
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
                print_checkpoint("PARSE", true, false);
                return false;
            }
    }
    return (print_checkpoint("PARSE", false, false), true);
}
