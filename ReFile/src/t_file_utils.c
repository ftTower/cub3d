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

#include "../includes/all.h"

void	t_file_null(t_file *file)
{
	file->nb_line = -1;
	file->fd = -1;
	file->pos = -1;
	file->lines = NULL;
	file->next = NULL;
	file->path = NULL;
	file->statut = STATUT_UNOPEN;
}

void	t_file_count_line(t_file *file)
{
	int		fd;
	char	*buf;

	fd = open(file->path, O_RDONLY);
	if (fd < 0)
		return ;
	buf = get_next_line(fd);
	if (buf)
		file->nb_line++;
	while (buf)
	{
		free(buf);
		buf = get_next_line(fd);
		file->nb_line++;
	}
	free(buf);
	close(fd);
}
