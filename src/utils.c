#include "cub3d.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\f' || c == '\n' || c == '\r' || c == '\t'
		|| c == '\v');
}

ssize_t	ft_atoi(const char *str)
{
	size_t		i;
	ssize_t			sign;
	ssize_t	num;

	i = 0;
	sign = 1;
	num = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign *= -1;
	while (str[i] >= '0' && str[i] <= '9')
		num = (num * 10) + (str[i++] - '0');
	return (num * sign);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*ptr_dst;

	if (dst == src)
		return (dst);
	ptr_dst = (unsigned char *)dst;
	while (n--)
		*ptr_dst++ = *(unsigned char *)src++;
	return (dst);
}

char    *path_format(char *str)
{
    char *ret;
    char **buf;

    buf = ft_split(str, ' ');
    if (!buf || !buf[0])
        return (NULL);
    ret = ft_strdup(buf[0]);
    if (!ret)
        return (t_rfree(buf), NULL);
    t_rfree(buf);
    buf = ft_split(ret, '\n');
    if (!buf || !buf[0])
        return (free(ret), NULL);
    free(ret);
    ret = ft_strdup(buf[0]);
    if (!ret)
        return (t_rfree(buf), NULL);
    return (free(str), t_rfree(buf), ret);
}

bool    is_map_char(char *map_chars, char c)
{
    ssize_t index;

    index = -1;
    while(map_chars[++index])
        if (map_chars[index] == c)
            return (true);
    return (false);
}

static char	*fill(int nb, long int nbr, int size)
{
	char	*str;

	if (nb == 0)
	{
		str = (char *)malloc(sizeof(char) * 2);
		if (!str)
			return (NULL);
		str[0] = '0';
		str[1] = '\0';
		return (str);
	}
	str = (char *)malloc(sizeof(char) * size);
	if (!str)
		return (NULL);
	str[size - 1] = '\0';
	size -= 2;
	while (nbr)
	{
		str[size--] = nbr % 10 + '0';
		nbr /= 10;
	}
	if (size == 0 && nb < 0)
		str[size] = '-';
	return (str);
}

static int	mal_size(int nb, long int nbr, int size)
{
	if (nb < 0)
		size += 2;
	else
		size += 1;
	while (nbr)
	{
		size++;
		nbr /= 10;
	}
	return (size);
}

char	*ft_itoa(int nb)
{
	long int	nbr;

	nbr = nb;
	if (nb < 0)
		nbr *= -1;
	return (fill(nb, nbr, mal_size(nb, nbr, 0)));
}