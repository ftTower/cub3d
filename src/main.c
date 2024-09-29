#include "cub3d.h"

int main(void)
{
    t_file *map;

    map = t_file_get("file.cub", STATUT_READ);

    t_file_print(map, PRINT_FULL);
    return (0);
}