/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 00:17:34 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/03/11 07:37:52 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
#define HEADER_H

#include "Libft/libft.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#include <dirent.h>
#include <readline/readline.h>


typedef struct s_env
{
    char *name;
    char *value;
    struct s_env *Next;
}t_env;



void add_env_var(t_env **my_envp, char *name, char *value);
t_env *init_envp(char **envp);
void my_unset(t_env *my_envp, char **args);
void  my_env(t_env *my_envp);
void my_export(t_env *my_envp, char **args);
int my_echo(t_env *my_envp, char **args);
void my_pwd( char **args);
void my_cd( char **args);
int execute_builtin(t_env *my_envp, char **args);

t_env *create_new(char *name, char *value);
void add_env_var(t_env **my_envp, char *name, char *value);


#endif