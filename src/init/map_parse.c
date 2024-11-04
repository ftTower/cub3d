#include "cub3d.h"

bool check_open_map(t_map *map)
{
    ssize_t h;
    ssize_t l;

    h = 0;
    l = 0;
    while(l < map->l)
        if (map->chunks[0][l++].type == CHUNK_EMPTY)
            return (true);
    while(h < map->h)
        if (map->chunks[h++][l - 1].type == CHUNK_EMPTY)
            return (true);
    while(l > 0)
        if (map->chunks[h - 1][l-- - 1].type == CHUNK_EMPTY)
            return (true);
    while(h > 0)
        if (map->chunks[h-- - 1][0].type == CHUNK_EMPTY)
            return (true);
    return (false);
}

void full_fill(t_map **map, ssize_t h, ssize_t l)
{

    if ((*map)->chunks[h][l].type != CHUNK_VOID && (*map)->chunks[h][l].type != CHUNK_PLAYER)
        return ;    
    (*map)->chunks[h][l].type = CHUNK_EMPTY;
    if (h > 0)
        full_fill(map, h - 1, l);
    if (l > 0)
        full_fill(map, h, l - 1);
    if (h < (*map)->h - 1)
        full_fill(map, h + 1, l);
    if (l < (*map)->l - 1)
        full_fill(map, h, l + 1);

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
                full_fill(&data->map, h, l);
                // data->map->chunks[h][l].type = CHUNK_PLAYER;
                // print_chunks(data->map);
                if (check_open_map(data->map))
                    return (print_checkpoint("PARSE", false, true), true);
                return false;
            }
    }
    return (true);
}
