#include "../includes/header.h"

void  my_env(t_env *custom_env)
{
	t_env *head;

	if (!custom_env)
		return ;
	head = custom_env;
	while (head)
	{
		// if (head->value)
		printf("%s=%s\n",head->key,head->value);
		head = head->next;
	}
	g_vars.g_exit_status = 0;
}