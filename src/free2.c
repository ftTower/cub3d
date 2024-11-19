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

void	t_rfree(char **ptr)
{
	ssize_t	index;

	index = -1;
	while (ptr[++index])
		free(ptr[index]);
	if (ptr)
		free(ptr);
}

void	t_free(void *ptr)
{
	if (ptr)
		free(ptr);
}

void	win_destructor(t_win *win)
{
	if (!win)
		return ;
	if (win->win_ptr)
		mlx_destroy_window(win->mlx_ptr, win->win_ptr);
	if (win->mlx_ptr)
	{
		mlx_destroy_display(win->mlx_ptr);
		free(win->mlx_ptr);
	}
	t_free(win->keys);
	t_free(win);
}
