#include "../includes/header.h"

void  my_env(t_env *custom_env)
{
	t_env *head;

	if (!custom_env)
		return ;
	head = custom_env;
	while (head)
	{
		printf("%s=%s\n",head->key,head->value);
		head = head->next;
	}
}