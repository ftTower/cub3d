#ifndef STRUCT_H
# define STRUCT_H

typedef enum   e_statut
{
    STATUT_READ,
    STATUT_WRITE,
    STATUT_ERROR,
    STATUT_UNOPEN,
}   t_statut;

typedef enum    e_print
{
    PRINT_FULL,
    PRINT_MEDIUM,
    PRINT_LIGHT,
}   t_print;

typedef struct s_line
{
    char *content;
    ssize_t pos;

    struct s_line *next;
}   t_line;

typedef struct s_file
{
    char *path;
    int fd;

    t_line *lines;
    
    t_statut statut;
    ssize_t nb_line;
    ssize_t pos;

    struct s_file *next;
}  t_file;

typedef struct s_binder
{
    t_file *files;


} t_binder;

#endif