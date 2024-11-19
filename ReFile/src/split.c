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

int	is_c(char c_s, char c)
{
	return (c_s == c);
}

unsigned int	count_word(char const *s, char c)
{
	size_t			i;
	unsigned int	count;

	i = 0;
	count = 0;
	while (s[i] && s[i + 1])
	{
		if (is_c(s[i], c) && !is_c(s[i + 1], c))
			count += 1;
		else if (i == 0 && !is_c(s[i], c))
			count += 1;
		i++;
	}
	return (count);
}

char	*mal_str(char const *s, char c, int *ptr)
{
	size_t	len;
	char	*dup;

	len = 0;
	while (is_c(s[*ptr], c) && s[*ptr])
		(*ptr)++;
	while (!is_c(s[*ptr], c) && s[*ptr])
	{
		(*ptr)++;
		len++;
	}
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	(*ptr) -= len;
	len = 0;
	while (!is_c(s[*ptr], c) && s[*ptr])
	{
		dup[len] = s[*ptr];
		(*ptr)++;
		len++;
	}
	dup[len] = '\0';
	return (dup);
}

char	**tab_tab_split(const char *s, char c)
{
	char	**tab;
	int		i;
	int		pos;
	int		count;

	i = 0;
	pos = 0;
	count = count_word(s, c);
	tab = (char **)malloc(sizeof(char *) * (count + 1));
	if (!tab)
		return (NULL);
	while (i < count)
	{
		pos = 0;
		tab[i] = mal_str(s, c, &pos);
		s += pos;
		i++;
	}
	tab[i] = 0;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab_split;

	if (!s)
		return (NULL);
	tab_split = tab_tab_split(s, c);
	return (tab_split);
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

	len1 = (s1 != NULL) ? f_strlen(s1) : 0;
	len2 = (s2 != NULL) ? f_strlen(s2) : 0;

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
