#include "header.h"


int main() 
{
    char *env = getenv("PATH");
    char *str = getcwd();
    printf("%s\n",env);    
    return (0);
}