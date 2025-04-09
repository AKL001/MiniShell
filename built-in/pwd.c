#include "../includes/header.h"
#include <stdio.h>

void my_pwd(char **args)
{
    char path[1024];

    if (getcwd(path,sizeof(path)) == NULL)
    {
        error_message("pwd: ",1);
        return ;
    }
    printf("%s\n",path);
}
