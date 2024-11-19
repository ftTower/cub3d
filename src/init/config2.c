/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:08:01 by marvin            #+#    #+#             */
/*   Updated: 2024/11/19 21:11:00 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	t_file_get_ptr(t_data *data, t_file **file, char *path)
{
	int	tex_width;
	int	tex_height;

	*file = t_file_get(path, STATUT_READ);
	if (!*file)
		return (true);
	(*file)->img = malloc(sizeof(t_img));
	if (!(*file)->img)
	{
		free(*file);
		return (true);
	}
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
	return ((*file)->img->width = tex_width,
		(*file)->img->height = tex_height, free(path), false);
}

bool	texture_init(t_data *data)
{
	data->config->ea = NULL;
	data->config->we = NULL;
	data->config->so = NULL;
	data->config->no = NULL;
	if (t_file_get_ptr(data, &data->config->ea,
			path_format(t_file_get_patern(data->config->map, "EA")))
		|| t_file_get_ptr(data, &data->config->we,
			path_format(t_file_get_patern(data->config->map, "WE")))
		|| t_file_get_ptr(data, &data->config->no,
			path_format(t_file_get_patern(data->config->map, "NO")))
		|| t_file_get_ptr(data, &data->config->so,
			path_format(t_file_get_patern(data->config->map, "SO"))))
		return (print_checkpoint("TEXTURE", false, false), true);
	return (false);
}

bool	rgb_init(char *str, ssize_t *r, ssize_t *g, ssize_t *b)
{
	char	**buf;

	buf = ft_split(str, ',');
	if (!buf)
		return (free(str), print_checkpoint("RGB", false, true), true);
	*r = 0;
	*g = 0;
	*b = 0;
	if (buf[0])
		*r = ft_atoi(buf[0]);
	if (buf[1])
		*g = ft_atoi(buf[1]);
	if (buf[2])
		*b = ft_atoi(buf[2]);
	return (free(str), t_rfree(buf), false);
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
