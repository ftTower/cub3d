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

#ifndef DEF_H
# define DEF_H

void    t_file_null(t_file *file);
void    t_file_count_line(t_file *file);
void    t_file_print(t_file *file, t_print grade);

char    *t_file_get_patern(t_file *file, char *patern);
char    *t_file_get_map(t_file *file, char *map_chars);
t_file *t_file_get(char *file_path, t_statut statut);
void    t_file_del(t_file *file);
bool    t_file_add(t_file **files, t_file *to_add);
bool t_file_open(t_file *file);

t_binder *t_binder_new(char *binder_name);
void t_binder_add_file(t_binder *binder, t_file *file_to_add);
void    t_binder_print(t_binder *binder);


size_t	f_strlen(const char *str);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
int	ft_strncmp(const char *s1, const char *s2, size_t n);

#endif