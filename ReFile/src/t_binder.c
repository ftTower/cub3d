/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_binder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 20:58:13 by tauer             #+#    #+#             */
/*   Updated: 2024/11/19 20:58:51 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/all.h"

void	t_binder_null(t_binder *binder)
{
	binder->name = NULL;
	binder->files = NULL;
}

t_binder	*t_binder_new(char *binder_name)
{
	t_binder	*new;

	new = malloc(sizeof(t_binder));
	if (!new)
		return (NULL);
	return (t_binder_null(new), new->name = binder_name, new);
}

void	t_binder_pos_update(t_binder *binder)
{
	t_file	*current;
	ssize_t	index;

	index = -1;
	current = binder->files;
	while (current)
	{
		current->pos = ++index;
		current = current->next;
	}
}

void	t_binder_add_file(t_binder *binder, t_file *file_to_add)
{
	t_file_add(&binder->files, file_to_add);
	t_binder_pos_update(binder);
}
