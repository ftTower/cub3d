#include "cub3d.h"

int main(int argc, char **argv)
{
    t_data data;

    if (argc != 2)
        return (1);
    else if (data_init(&data, argv[1]))
        return (data_destructor(&data), 1);

    return (data_destructor(&data), 0);
}