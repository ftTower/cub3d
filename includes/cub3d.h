#ifndef CUB3D_H
#define CUB3D_H

#include "../Refile/includes/all.h"


typedef struct s_config
{
    char *NO;
    char *SO;
    char *WE;
    char *EA;

    ssize_t screen_w;
    ssize_t screen_h;

    ssize_t f_r;
    ssize_t f_g;
    ssize_t f_b;

    ssize_t c_r;
    ssize_t c_g;
    ssize_t c_b;

}   t_config;

typedef struct s_data
{
    t_config *map;
    

}   t_data;

#endif