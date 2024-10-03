#include "cub3d.h"

bool    full_fill(t_map *map, ssize_t h, ssize_t l)
{
    map->chunks[h][l].type = CHUNK_EMPTY;
    if (h == 0 || l == 0 || h == map->h  - 1|| l == map->l - 1)
        return (true);
    if (map->chunks[h - 1][l].type == CHUNK_VOID)
        full_fill(map, h - 1, l);
    if (map->chunks[h + 1][l].type == CHUNK_VOID)
        full_fill(map, h + 1, l);
    if (map->chunks[h][l - 1].type == CHUNK_VOID)
        full_fill(map, h, l -1);
    if (map->chunks[h][l + 1].type == CHUNK_VOID)
        full_fill(map, h, l + 1);
    return (false);
}

bool    fill_check(t_map *map)
{
    ssize_t h;
    ssize_t l;

    
    h = -1;
    while(++h < map->h)
    {
        l = -1;
        while(++l < map->l)
            if (map->chunks[h][l].type == CHUNK_PLAYER)
                return (full_fill(map, h, l), map->chunks[h][l].type = CHUNK_PLAYER ,print_chunks(map), print_checkpoint("PARSE", true, false), false);
    }
    return (print_checkpoint("PARSE", false, false), true);
}
