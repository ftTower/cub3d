/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_lines.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:59:39 by tauer             #+#    #+#             */
/*   Updated: 2024/11/19 21:08:05 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/all.h"

bool	t_lines_add(t_line **lines, t_line *line)
{
	t_line	*current;

	if (!line)
		return (true);
	else if (!*lines)
		return (*lines = line, false);
	current = *lines;
	while (current->next)
		current = current->next;
	return (current->next = line, false);
}

t_line	*t_line_new(char *line)
{
	t_line	*new;

	new = malloc(sizeof(t_line));
	if (!new)
		return (NULL);
	if (!line)
	{
		free(new);
		return (NULL);
	}
	new->content = ft_strdup(line);
	if (!new->content)
		return (NULL);
	new->next = NULL;
	return (new);
}

void	t_line_pos_update(t_line *line)
{
	t_line	*current;
	ssize_t	pos;

	pos = -1;
	current = line;
	while (current)
	{
		current->pos = ++pos;
		current = current->next;
	}
}

void	t_file_lines_update(t_file *file)
{
	int		fd;
	char	*buf;

	fd = open(file->path, O_RDONLY);
	if (fd < 0)
		return ;
	buf = get_next_line(fd);
	if (buf)
		t_lines_add(&file->lines, t_line_new(buf));
	while (buf)
	{
		free(buf);
		buf = get_next_line(fd);
		if (buf)
			t_lines_add(&file->lines, t_line_new(buf));
	}
	free(buf);
	close(fd);
	t_line_pos_update(file->lines);
}
