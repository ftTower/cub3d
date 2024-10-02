#include "cub3d.h"

void    print_checkpoint(char *checkpoint_name, bool succeed, bool lignfeed)
{
    char* colors[3] = {
        "\033[48;5;196m",  // Rouge
        "\033[48;5;28m",  // Vert
        "\033[0m"      // Fin de séquence
    };
    if (succeed)
        printf("%s%-9.8s %s",colors[1], checkpoint_name, colors[2]);
    else
        printf("%s%-9.8s %s",colors[0], checkpoint_name, colors[2]);
    if (lignfeed)
        printf("\n");
}

void    print_config(t_config *config)
{
    char* colors[11] = {
    "\033[48;5;1m",   // Rouge
    "\033[48;5;2m",   // Vert
    "\033[48;5;3m",   // Jaune
    "\033[48;5;4m",   // Bleu
    "\033[48;5;5m",   // Magenta
    "\033[48;5;6m",   // Cyan
    "\033[48;5;9m",   // Rouge clair
    "\033[48;5;61m",  // Vert clair
    "\033[48;5;60m",  // violet
    "\033[48;5;59m",  // antracite
    "\033[0m"         // Fin de séquence
};
    printf("%s %s : %s%s %-4ld   %s%s   %-4ld%s\n", colors[9],"R", colors[10], colors[8],config->r_w, colors[10], colors[7],config->r_h, colors[10] );
    printf("%s %s : %s%s %-4ld%s%s %-4ld%s%s %-4ld%s\n",colors[9],"F", colors[10], colors[0], config->f_r ,colors[10], colors[1], config->f_g ,colors[10], colors[3], config->f_b ,colors[10]);
    printf("%s %s : %s%s %-4ld%s%s %-4ld%s%s %-4ld%s\n",colors[9],"C", colors[10], colors[0], config->c_r ,colors[10], colors[1], config->c_g ,colors[10], colors[3], config->c_b ,colors[10]);
}