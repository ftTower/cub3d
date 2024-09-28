#include "../includes/all.h"

void free_split(char **split)
{
    ssize_t i = 0;

    if (!split)
        return;
    while (split[i])
        free(split[i++]);
    free(split);
}

char *t_file_get_patern(t_file *file, char *patern)
{
    t_line *current;
    char **buf;
    ssize_t index;

    buf = NULL;
    current = file->lines;
    while (current)
    {
        buf = ft_split(current->content, ' ');
        if (!buf)
            return (NULL);
        index = -1;
        while (buf[++index])
            if (!ft_strncmp(buf[index], patern, f_strlen(patern) + 1))
            {
                char *result = ft_strdup(current->content + f_strlen(patern));
                free_split(buf);
                return result;
            }
        free_split(buf);
        current = current->next;
    }
    return (NULL);
}

bool    are_all_chars_in_str(char *str, char *allowed_chars)
{
    ssize_t  index;
    ssize_t  char_index;

    if (!str || !allowed_chars)
        return (false);
    
    index = -1;
    while (str[++index])
    {
        char_index = -1;
        while (allowed_chars[++char_index])
            if (allowed_chars[char_index] == str[index])
                break;
        if (!allowed_chars[char_index])
            return (false);
    }
    return (true);
}


char *t_file_get_map(t_file *file, char *map_chars)
{
    t_line *current;
    char *buf = ft_strdup("");
    char *tmp;
    char *line_with_newline;

    current = file->lines;
    while (current)
    {
        if (are_all_chars_in_str(current->content, map_chars))
        {
            line_with_newline = ft_strjoin(current->content, "\n");
            tmp = ft_strjoin(buf, line_with_newline);
            free(buf);
            free(line_with_newline);
            buf = tmp;
        }
        current = current->next;
    }
    return (buf);
}
