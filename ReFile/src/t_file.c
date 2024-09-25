#include "../includes/all.h"
#include <string.h>

bool     t_file_open(t_file *file)
{
    if (file->statut == STATUT_READ)
        file->fd = open(file->path, O_RDONLY);
    else if (file->statut == STATUT_WRITE)
        file->fd = open(file->path, O_WRONLY);
    if (file->fd < 0)
        return (true);
    return (false);
}

bool    t_lines_add(t_line **lines, t_line *line)
{
    t_line *current;

    if (!line)
        return (true);
    else if (!*lines)
        return (*lines = line ,false);
    current = *lines;
    while(current->next)
        current = current->next;
    return (current->next = line, false);
}

t_line  *t_line_new(char *line)
{
    t_line *new;

    new = malloc(sizeof(t_line));
    if (!new)
        return (NULL);
    if (!line)
    {
        free(new);
        return (NULL);
    }
    new->content = strdup(line);
    new->next = NULL;
    return (new);
}

void    t_line_pos_update(t_line *line)
{
    t_line *current;
    ssize_t pos;

    pos = -1;
    current = line;
    while(current)
    {
        current->pos = ++pos;
        current = current->next;
    }
}

void    t_file_lines_update(t_file *file)
{
    int fd;
    char *buf;

    fd = open(file->path, O_RDONLY);
    if (fd < 0)
        return ;
    // if   lines
    //      free ancienne lines
    buf = get_next_line(fd);
    if (buf)
        t_lines_add(&file->lines, t_line_new(buf));
    while(buf)
    {
        free(buf);
        buf = get_next_line(fd);
        if (buf)
            t_lines_add(&file->lines, t_line_new(buf));
    }
    free(buf);
    close (fd);
    t_line_pos_update(file->lines);
}

t_file *t_file_new(void)
{
    t_file *new;

    new = malloc(sizeof(t_file));
    return (t_file_null(new), new);
}

t_file *t_file_get(char *file_path, t_statut statut)
{
    t_file *ret;

    ret = t_file_new();

    ret->statut = statut;
    ret->path = file_path;

    if (t_file_open(ret))
        return (t_file_print(ret, PRINT_LIGHT), NULL);

    t_file_count_line(ret);
    t_file_lines_update(ret);
    return (t_file_print(ret, PRINT_LIGHT) ,ret);
}


void    t_file_del(t_file *file)
{
    t_line *current, *buf;
    
    current = file->lines;
    while(current)
    {
        buf = current->next;
        free(current->content);
        free(current);
        current = buf;
    }
    free(file);
}