#include "cub3d.h"

void    config_print(t_config *config)
{
    char* colors[11] = {
        "\033[0;31m",  // Rouge
        "\033[0;32m",  // Vert
        "\033[0;33m",  // Jaune
        "\033[0;34m",  // Bleu
        "\033[0;35m",  // Magenta
        "\033[0;36m",  // Cyan
        "\033[1;31m",  // Rouge clair
        "\033[1;32m",  // Vert clair
        "\033[1;33m",  // Jaune clair
        "\033[1;34m",  // Bleu clair
        "\033[0m"      // Fin de séquence
    };
    printf("%sTEXTURES%s\n", colors[5], colors[10]);
    printf("%sNO%s%s%s%s", colors[2], colors[10], colors[3], config->NO, colors[10]);
    printf("%sSO%s%s%s%s", colors[2], colors[10], colors[3], config->SO, colors[10]);
    printf("%sWE%s%s%s%s", colors[2], colors[10], colors[3], config->WE, colors[10]);
    printf("%sEA%s%s%s%s", colors[2], colors[10], colors[3], config->EA, colors[10]);
    
    printf("%sData%s\n", colors[5], colors[10]);
    printf("%sR %s%s%s%s", colors[2], colors[10], colors[3], config->reso, colors[10]);
    printf("%sF %s%s%s%s", colors[2], colors[10], colors[3], config->f_rgb, colors[10]);
    printf("%sC %s%s%s%s", colors[2], colors[10], colors[3], config->c_rgb, colors[10]);



}

void    config_null(t_config *config)
{
    config->NO = NULL;
    config->SO = NULL;
    config->EA = NULL;
    config->WE = NULL;
    config->f_rgb = NULL;
    config->c_rgb = NULL;
    config->reso = NULL;
    config->map = NULL;

}

bool    config_init(t_data *data, char *filepath)
{
    data->config = malloc(sizeof(t_config));
    if (!data->config)
        return (true);
    config_null(data->config);
    data->config->map = t_file_get(filepath, STATUT_READ);
    data->config->EA = t_file_get_patern(data->config->map, "EA");
    data->config->WE = t_file_get_patern(data->config->map, "WE");
    data->config->NO = t_file_get_patern(data->config->map, "NO");
    data->config->SO = t_file_get_patern(data->config->map, "SO");
    data->config->reso = t_file_get_patern(data->config->map, "R");
    data->config->f_rgb = t_file_get_patern(data->config->map, "F");
    data->config->c_rgb = t_file_get_patern(data->config->map, "C");
    return (config_print(data->config),false);
}

bool    data_init(t_data *data, char *filepath)
{
    data->config = NULL;
    if (config_init(data, filepath))
        return (true);
    return (false);
}

int main(int argc, char **argv)
{
    t_data data;

    if (argc != 2)
        return (1);
    else if (data_init(&data, argv[1]))
        return (2);
    

    return (data_destructor(&data), 0);
}