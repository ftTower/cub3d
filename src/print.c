/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:08:01 by marvin            #+#    #+#             */
/*   Updated: 2024/06/05 18:08:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_checkpoint(char *checkpoint_name, bool succeed, bool lignfeed)
{
	static char	*colors[3] = {
		"\033[48;5;196m",
		"\033[48;5;28m",
		"\033[0m"
	};

	if (succeed)
		printf("%s%-9.8s %s", colors[1], checkpoint_name, colors[2]);
	else
		printf("%s%-9.8s %s", colors[0], checkpoint_name, colors[2]);
	if (lignfeed)
		printf("\n");
}

int	print_key(t_win *win)
{
	static char	*colors[3] = {
		"\033[48;5;1m",
		"\033[48;5;2m",
		"\033[0m"
	};

	if (win->keys[KEY_UP])
		printf("KEY UP : %s %s\n", colors[1], colors[2]);
	else
		printf("KEY UP : %s %s\n", colors[0], colors[2]);
	if (win->keys[KEY_DOWN])
		printf("KEY DOWN : %s %s\n", colors[1], colors[2]);
	else
		printf("KEY DOWN : %s %s\n", colors[0], colors[2]);
	if (win->keys[KEY_LEFT])
		printf("KEY LEFT : %s %s\n", colors[1], colors[2]);
	else
		printf("KEY LEFT : %s %s\n", colors[0], colors[2]);
	if (win->keys[KEY_RIGHT])
		printf("KEY RIGHT : %s %s\n", colors[1], colors[2]);
	else
		printf("KEY RIGHT : %s %s\n", colors[0], colors[2]);
	return (0);
}

void	print_config(t_config *config)
{
	static char	*colors[11] = {
		"\033[48;5;1m",
		"\033[48;5;2m",
		"\033[48;5;3m",
		"\033[48;5;4m",
		"\033[48;5;5m",
		"\033[48;5;6m",
		"\033[48;5;9m",
		"\033[48;5;61m",
		"\033[48;5;60m",
		"\033[48;5;59m",
		"\033[0m"
	};

	printf("\n%s %s : %s%s %-4ld   %s%s   %-4ld%s\n",
		colors[9], "R", colors[10], colors[8], config->r_w, colors[10],
		colors[7], config->r_h, colors[10]);
	printf("%s %s : %s%s %-4ld%s%s %-4ld%s%s %-4ld%s\n",
		colors[9], "F", colors[10], colors[0], config->f_r, colors[10],
		colors[1], config->f_g, colors[10], colors[3], config->f_b, colors[10]);
	printf("%s %s : %s%s %-4ld%s%s %-4ld%s%s %-4ld%s\n",
		colors[9], "C", colors[10], colors[0], config->c_r, colors[10],
		colors[1], config->c_g, colors[10], colors[3], config->c_b, colors[10]);
}

void	print_chunks(t_map *map)
{
	ssize_t			h;
	ssize_t			l;
	static char		*colors[5] = {"\033[48;5;1m",
		"\033[48;5;0m",
		"\033[48;5;2m", "\033[0m", "\033[48;5;4m"};

	h = -1;
	l = -1;
	printf("\n");
	while (++h < map->h)
	{
		l = -1;
		while (++l < map->l)
		{
			if (map->chunks[h][l].type == CHUNK_EMPTY)
				printf("%sE%s", colors[2], colors[3]);
			else if (map->chunks[h][l].type == CHUNK_VOID)
				printf("%sV%s", colors[0], colors[3]);
			else if (map->chunks[h][l].type == CHUNK_WALL)
				printf("%sW%s", colors[1], colors[3]);
			else if (map->chunks[h][l].type == CHUNK_PLAYER)
				printf("%sP%s", colors[4], colors[3]);
		}
		printf("\n");
	}
}
