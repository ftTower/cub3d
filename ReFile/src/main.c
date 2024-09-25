#include "../includes/all.h"

int	main(void)
{
    t_file *new_file, *new_file2;

	new_file =  t_file_get("file.cub", STATUT_READ);
    new_file2 = t_file_get("file2.cub", STATUT_READ);
    // t_file_get("tes04efefefsefsefse", STATUT_READ);


    t_file_del(new_file);
    t_file_del(new_file2);
	return (0);
}