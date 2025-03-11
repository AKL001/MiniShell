#ifndef GLOBAL_H
#define GLOBAL_H

typedef struct s_env
{
    char *name;
    char *value;
    struct s_env *Next;
}t_env;

extern  t_env *my_envp;

#endif 