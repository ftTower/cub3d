#ifndef DEF_H
# define DEF_H

void    t_file_null(t_file *file);
void    t_file_count_line(t_file *file);
void    t_file_print(t_file *file, t_print grade);


t_file *t_file_get(char *file_path, t_statut statut);
void    t_file_del(t_file *file);



#endif