#ifndef CUB3D_H
#define CUB3D_H

#include "../Refile/includes/all.h"

typedef struct s_config
{
    char *NO;
    char *SO;
    char *WE;
    char *EA;

    char *reso;

    char *f_rgb;
    char *c_rgb;

    t_file *map;
}   t_config;

typedef struct s_data
{
    t_config *config;
    

}   t_data;

void data_destructor(t_data *data);
void config_destructor(t_config *config);


#endif