#include "../includes/header.h"
#include <stdio.h>

void my_pwd(char **args)
{
    char path[1024];

    if (args[1])
    {
        perror("pwd: ");
        return ;
    }
    if (getcwd(path,sizeof(path)) == NULL)
        return ;
    // if (path)
    printf("%s\n",path);
}
