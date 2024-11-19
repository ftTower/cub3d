/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:08:01 by marvin            #+#    #+#             */
/*   Updated: 2024/11/19 20:00:01 by tauer            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
}					t_img;

typedef enum e_statut
{
	STATUT_READ,
	STATUT_WRITE,
	STATUT_ERROR,
	STATUT_UNOPEN,
}					t_statut;

typedef enum e_print
{
	PRINT_FULL,
	PRINT_MEDIUM,
	PRINT_LIGHT,
}					t_print;

typedef struct s_line
{
	char			*content;
	ssize_t			pos;

	struct s_line	*next;
}					t_line;

typedef struct s_file
{
	char			*path;
	int				fd;

	t_line			*lines;

	t_statut		statut;

	t_img			*img;
	ssize_t			nb_line;
	ssize_t			pos;

	void			*mlx_img;
	struct s_file	*next;
}					t_file;

typedef struct s_binder
{
	char			*name;
	t_file			*files;

}					t_binder;

#endif