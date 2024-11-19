/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_file.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:08:01 by marvin            #+#    #+#             */
/*   Updated: 2024/11/19 21:01:24 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/all.h"
#include <string.h>

bool	t_file_open(t_file *file)
{
	if (file->statut == STATUT_READ)
		file->fd = open(file->path, O_RDONLY);
	else if (file->statut == STATUT_WRITE)
		file->fd = open(file->path, O_WRONLY);
	if (file->fd < 0)
		return (true);
	return (false);
}

bool	t_file_add(t_file **files, t_file *to_add)
{
	t_file	*current;

	if (!files)
		return (true);
	else if (!*files)
		return (*files = to_add, false);
	current = *files;
	while (current->next)
		current = current->next;
	return (current->next = to_add, false);
}

t_file	*t_file_new(void)
{
	t_file	*new;

	new = malloc(sizeof(t_file));
	return (t_file_null(new), new);
}

t_file	*t_file_get(char *file_path, t_statut statut)
{
	t_file	*ret;

	ret = t_file_new();
	ret->statut = statut;
	ret->img = NULL;
	ret->path = ft_strdup(file_path);
	if (t_file_open(ret))
		return (t_file_print(ret, PRINT_LIGHT), free(ret->path), free(ret),
			NULL);
	t_file_count_line(ret);
	t_file_lines_update(ret);
	ret->pos = 0;
	t_file_print(ret, PRINT_LIGHT);
	return (ret);
}

void	t_file_del(t_file *file)
{
	t_line	*current;
	t_line	*buf;

	if (file)
	{
		current = file->lines;
		while (current)
		{
			buf = current->next;
			free(current->content);
			free(current);
			current = buf;
		}
		if (file->fd > 0)
			close(file->fd);
		if (file->path)
			free(file->path);
		if (file)
			free(file);
	}
}
