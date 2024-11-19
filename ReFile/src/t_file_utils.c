/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_file_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tauer <tauer@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 18:08:01 by marvin            #+#    #+#             */
/*   Updated: 2024/11/19 21:25:16 by tauer            ###   ########.fr       */
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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	while (n > 0)
	{
		if (*s1 != *s2 || *s1 == '\0' || *s2 == '\0')
			return ((unsigned char)*s1 - (unsigned char)*s2);
		s1++;
		s2++;
		n--;
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	char	*result;
	size_t	len1;
	size_t	len2;

	len1 = 0;
	len2 = 0;
	if (s1)
		len1 = f_strlen(s1);
	if (s2)
		len2 = f_strlen(s2);
	str = (char *)malloc(sizeof(char) * (len1 + len2 + 1));
	if (!str)
		return (NULL);
	result = str;
	if (s1 != NULL)
		while (*s1)
			*str++ = *s1++;
	if (s2 != NULL)
		while (*s2)
			*str++ = *s2++;
	*str = '\0';
	return (result);
}
