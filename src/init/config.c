#include "cub3d.h"

bool	t_file_get_ptr(t_data *data, t_file **file, char *path)
{
	// Charger la texture depuis un fichier XPM avec sa taille réelle
	int tex_width, tex_height;
	*file = t_file_get(path, STATUT_READ);
	if (!*file)
		return (true);
	(*file)->img = malloc(sizeof(t_img));
	if (!(*file)->img)
	{
		free(*file);
		return (true);
	}
	// Charger l'image à partir du fichier XPM avec la vraie taille
	(*file)->img->img = mlx_xpm_file_to_image(data->win->mlx_ptr, path,
			&tex_width, &tex_height);
	if (!(*file)->img->img)
	{
		free((*file)->img);
		free(*file);
		return (true);
	}
	(*file)->img->addr = mlx_get_data_addr((*file)->img->img,
			&(*file)->img->bits_per_pixel, &(*file)->img->line_length,
			&(*file)->img->endian);
	(*file)->img->width = tex_width;
	(*file)->img->height = tex_height;
	free(path);
	return (false);
}

bool	texture_init(t_data *data)
{
	data->config->EA = NULL;
	data->config->WE = NULL;
	data->config->SO = NULL;
	data->config->NO = NULL;
	if (t_file_get_ptr(data, &data->config->EA,
			path_format(t_file_get_patern(data->config->map, "EA")))
		|| t_file_get_ptr(data, &data->config->WE,
			path_format(t_file_get_patern(data->config->map, "WE")))
		|| t_file_get_ptr(data, &data->config->NO,
			path_format(t_file_get_patern(data->config->map, "NO")))
		|| t_file_get_ptr(data, &data->config->SO,
			path_format(t_file_get_patern(data->config->map, "SO"))))
		return (print_checkpoint("TEXTURE", false, false), true);
	return (false);
}

bool	rgb_init(char *str, ssize_t *r, ssize_t *g, ssize_t *b)
{
	char	**buf;

	buf = ft_split(str, ',');
	if (!buf)
		return (free(str), print_checkpoint("RGB", false, true),true);
	*r = 0;
	*g = 0;
	*b = 0;
	if (buf[0])
		*r = ft_atoi(buf[0]);
	if (buf[1])
		*g = ft_atoi(buf[1]);
	if (buf[2])
		*b = ft_atoi(buf[2]);
	return (free(str), t_rfree(buf),false);
}

bool	res_init(char *str, ssize_t *w, ssize_t *h)
{
	char	**buf;

	buf = ft_split(str, ' ');
	if (!buf)
		return (free(str), print_checkpoint("RESOLUTION", false, true), true);
	*w = 0;
	*h = 0;
	if (buf[0])
		*w = ft_atoi(buf[0]);
	if (buf[1])
		*h = ft_atoi(buf[1]);
	return (free(str), t_rfree(buf), false);
}

bool	config_init(t_data *data, char *filepath)
{
	data->config = malloc(sizeof(t_config));
	if (!data->config)
		return (print_checkpoint("CONFIG", false, true), true);
	data->config->map = t_file_get(filepath, STATUT_READ);
	if (!data->config->map || rgb_init(t_file_get_patern(data->config->map,
				"C"), &data->config->c_r, &data->config->c_g,
			&data->config->c_b) || rgb_init(t_file_get_patern(data->config->map,
				"F"), &data->config->f_r, &data->config->f_g,
			&data->config->f_b) || res_init(t_file_get_patern(data->config->map,
				"R"), &data->config->r_w, &data->config->r_h))
		return (print_checkpoint("CONFIG", false, true), true);
	return (false);
}

bool	key_init(t_data *data)
{
	data->win->keys = malloc(sizeof(bool) * 9);
	if (!data->win->keys)
		return (true);
	data->win->keys[KEY_UP] = false;
	data->win->keys[KEY_DOWN] = false;
	data->win->keys[KEY_LEFT] = false;
	data->win->keys[KEY_RIGHT] = false;
	data->win->keys[KEY_PLUS] = false;
	data->win->keys[KEY_MINUS] = false;
	data->win->keys[KEY_ARROW_LEFT] = false;
	data->win->keys[KEY_ARROW_RIGHT] = false;
	data->win->keys[KEY_VIEW_SWITCH] = false;
	return (false);
}

bool	win_init(t_data *data)
{
	data->win = malloc(sizeof(t_win));
	if (!data->win || key_init(data))
		return (true);
	data->win->mlx_ptr = mlx_init();
	data->win->win_ptr = mlx_new_window(data->win->mlx_ptr, data->config->r_w,
			data->config->r_h, "CUB3D");
	return (data->win->map_view = false, data->win->chunk_size = 20, false);
}

bool	player_init(t_data *data)
{
	data->player = malloc(sizeof(t_player));
	if (!data->player)
		return (true);
	data->player->x = 0;
	data->player->y = 0;
	data->player->angle = -90.0f;
	data->player->fov = 60.0f;
	return (false);
}

bool	data_init(t_data *data, char *filepath)
{
	data->map = NULL;
	data->config = NULL;
	data->player = NULL;
	data->win = NULL;
	if (config_init(data, filepath) || win_init(data) || texture_init(data)
		|| map_init(data) || player_init(data) || fill_check(data))
		return (print_checkpoint("DATA", false, true), true);
	return (print_config(data->config), false);
}
