#ifndef CUB3D_H
#define CUB3D_H

#include "../Refile/includes/all.h"

typedef struct s_config
{
    char *NO;
    char *SO;
    char *WE;
    char *EA;

    ssize_t r_w;
    ssize_t r_h;

    ssize_t f_r;
    ssize_t f_g;
    ssize_t f_b;

    ssize_t c_r;
    ssize_t c_g;
    ssize_t c_b;

    t_file *map;
}   t_config;

typedef struct s_data
{
    t_config *config;
    

}   t_data;

//!init
bool    texture_init(t_data *data);
bool    rgb_init(char *str, ssize_t *r, ssize_t *g, ssize_t *b);
bool    config_init(t_data *data, char *filepath);
bool    data_init(t_data *data, char *filepath);

//!utils
ssize_t	ft_atoi(const char *str);
char    *path_format(char *str);

//!free
void t_free(void *ptr);
void t_rfree(char **ptr);
void data_destructor(t_data *data);
void config_destructor(t_config *config);

//!print
void    print_checkpoint(char *checkpoint_name, bool succeed, bool lignfeed);
void    print_config(t_config *config);

#endif