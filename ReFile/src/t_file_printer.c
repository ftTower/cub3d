/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_file_printer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:08:01 by marvin            #+#    #+#             */
/*   Updated: 2024/11/19 21:06:03 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/all.h"

void	t_file_print_info(t_file *file, const char **colors)
{
	if (file->pos < 0)
		printf("%s ❌  %s", colors[1], colors[8]);
	else
		printf("%s %-3ld %s", colors[1], file->pos, colors[8]);
	if (file->fd < 0)
		printf("%s   ❌   %s", colors[2], colors[8]);
	else
		printf("%s fD %-3d %s", colors[2], file->fd, colors[8]);
	if (file->nb_line < 0)
		printf("%s     ❌     %s", colors[3], colors[8]);
	else
		printf("%s %-5.5ld lines | %s", colors[3], file->nb_line, colors[8]);
}

void	t_file_print_line(t_file *file, const char **colors, int grade, int len)
{
	t_line	*current;
	char	*buf;
	ssize_t	index;
	ssize_t	compare;

	buf = NULL;
	compare = 0;
	current = file->lines;
	while (current)
	{
		if (len > 0 && compare > len)
			break ;
		compare++;
		printf("\n%s %-4ld %s", colors[0], current->pos, colors[8]);
		buf = ft_substr(current->content, 0, grade);
		index = -1;
		while (buf[++index])
			if (buf[index] != '\n')
				printf("%s%c%s", colors[7], buf[index], colors[8]);
		free(buf);
		current = current->next;
	}
}

void	t_file_print(t_file *file, t_print grade)
{
	const char	*colors[] = {
		"\033[48;5;58m",
		"\033[48;5;59m",
		"\033[48;5;60m",
		"\033[48;5;61m",
		"\033[48;5;62m",
		"\033[48;5;63m",
		"\033[48;5;64m",
		"\033[48;5;65m",
		"\033[0m",
	};

	if (grade == PRINT_LIGHT)
	{
		t_file_print_info(file, colors);
		printf("%s %-32.31s%s", colors[4], file->path, colors[8]);
		printf("\n");
	}
}

void	t_binder_print(t_binder *binder)
{
	t_file	*current;

	printf("%s\n", binder->name);
	current = binder->files;
	while (current)
	{
		t_file_print(current, PRINT_LIGHT);
		current = current->next;
	}
	printf("\n");
}
