#include "../includes/header.h"

void my_cd(char **args)
{
    DIR *dir;

    if (args[1] == NULL)
    {
        dir = opendir("~");
        // printf("cd => %s , %s\n",args[0],args[1]);
    }
    else 
        dir = opendir(args[1]);
    if (!dir)
    {
        perror(args[1]);
        return;
    }

    closedir(dir);

    if (chdir(args[1]) != 0)
    {
        perror("cd");
    }
}
