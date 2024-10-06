#ifndef CUB3D_H
#define CUB3D_H

#include "../Refile/includes/all.h"
#include "../minilibx-linux/mlx.h"
#include <math.h>

#define PI M_PI
#define PI_OVER_2 (PI / 2)  // 90 degrés
#define PI_OVER_4 (PI / 4)  // 45 degrés
#define TWO_PI (2 * PI)     // 360 degrés


typedef enum e_chunk_type
{
    CHUNK_WALL,
    CHUNK_EMPTY,
    CHUNK_VOID,
    CHUNK_PLAYER,
}   t_chunk_type;

typedef enum e_vision
{
    VISION_MAP,
    VISION_FPV,
    VISION_BORDER,
}   t_vision;

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

typedef struct s_chunk
{
    t_chunk_type type;
}   t_chunk;

typedef struct s_map
{
    t_chunk **chunks;
    ssize_t l;
    ssize_t h;
}   t_map;

typedef enum   s_key
{
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_PLUS,
    KEY_MINUS,
    KEY_ARROW_LEFT,
    KEY_ARROW_RIGHT,
}   t_key;

typedef struct s_img
{
    void    *img;          // Pointeur vers l'image MLX
    char    *addr;         // Adresse de la mémoire de l'image
    int     bits_per_pixel; // Nombre de bits par pixel
    int     line_length;    // Taille d'une ligne de l'image en mémoire
    int     endian;         // Endian (ordre des octets)
    int     width;          // Largeur de l'image
    int     height;         // Hauteur de l'image
}               t_img;

typedef struct s_win
{
    bool    *keys;
    void    *mlx_ptr;
    void    *win_ptr;

    ssize_t chunk_size;
    int     offset_x;
    int     offset_y;
}   t_win;

typedef struct s_player
{
    float   x;
    float   y;
    float   angle; 
}   t_player;

typedef struct s_data
{
    t_config *config;
    t_map    *map;
    t_win    *win;
    t_player *player;
}   t_data;

//!config
bool    texture_init(t_data *data);
bool    rgb_init(char *str, ssize_t *r, ssize_t *g, ssize_t *b);
bool    config_init(t_data *data, char *filepath);
bool    data_init(t_data *data, char *filepath);

//!map
bool    map_init(t_data *data);


//!utils
ssize_t	ft_atoi(const char *str);
char    *path_format(char *str);
bool    is_map_char(char *map_chars, char c);
char	*ft_itoa(int nb);

//!free
void t_free(void *ptr);
void t_rfree(char **ptr);
void data_destructor(t_data *data);
void config_destructor(t_config *config);

//!print
void    print_checkpoint(char *checkpoint_name, bool succeed, bool lignfeed);
void    print_config(t_config *config);
void    print_chunks(t_map *map);

//!full fill
bool    full_fill(t_map *map, ssize_t h, ssize_t l);
bool    fill_check(t_data *data);

//!game
int    game(t_data * data);
int    key_press(int keycode, t_data *data);
int    key_release(int keycode, t_data *data);
int    print_key(t_win *win);
void   update_player(t_data *data);

//!img
void    img_refresh(t_data *data);
void    my_mlx_pixel_put(t_img *img, int x, int y, int color);
void    img_draw(t_data *data, t_vision vision, t_img *img);
void    img_put_stat(t_data *data);
void    img_null_pixel(t_data *data, t_img *img);
void img_draw_map(t_data *data, t_img *img);

void    handle_vision(t_data *data, t_img *img);

#endif