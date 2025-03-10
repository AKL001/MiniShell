/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 00:17:34 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/03/10 07:42:35 by ael-aiss         ###   ########.fr       */
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
#include <readline/readline.h>
#include "global.h"

typedef struct exec_function
{
    char *name;
    int (*func)(char **args);
}builtin_cmd;




void add_env_var(char *name, char *value);
void init_envp(char **envp);
void my_unset(char **args);
void  my_env();
void my_export(char **args);
int my_echo(char **args);
int execute_builtin(char **args);

#endif