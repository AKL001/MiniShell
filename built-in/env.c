#include "../header.h"

void  my_env()
{
    t_env *head;

    head = my_envp;
    while (head)
    {
        printf("%s=%s\n",head->name,head->value);
        head = head->Next;
    }
}