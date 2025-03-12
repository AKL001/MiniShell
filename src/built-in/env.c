#include "../../includes/header.h"

void  my_env(t_env *my_envp)
{
	t_env *head;

	if (!my_envp)
		return ;
	head = my_envp;
	while (head)
	{
		printf("%s=%s\n",head->name,head->value);
		head = head->Next;
	}
}