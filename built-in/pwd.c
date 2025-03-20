#include "../../includes/header.h"

void my_pwd(char **args)
{
    char path[1024];

    if (args[1])
    {
        perror("pwd: ");
        return ;
    }
    getcwd(path,sizeof(path));
    if (path)
        printf("%s\n",path);
}
