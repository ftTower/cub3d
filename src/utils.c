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