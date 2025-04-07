/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_var.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 07:09:39 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/07 10:31:45 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int is_escaped(char *arg)
{
    int i;

    i = 0;
    while (arg[i])
    {
        if (arg[i] == '$' && i != 0)
        {
            if (arg[i - 1] == '\\')
                return (1);
        }
        i++;
    }
    return (0);
}

int does_dollar_exist(char *arg)
{
    int i = 0;
    if (!arg)
        return (0);
    while (arg[i])
    {
        if (arg[i] == '$')
        {
            if (i != 0)
            {
                if (arg[i - 1] == '\\')
                    return (0);
            }
            return (1);
        }
        i++;
    }
    return (0);
}

char *is_valid_key(char *arg)
{
    int i = 0;
    if (is_escaped(arg))
        return (NULL);
    while (arg[i] != '$')
        i++;
    if (arg[i] == '\0')
        return (NULL);
    int len = 0;
    i++;
    while (arg[i] && arg[i] != '"' && arg[i] != '\'' && arg[i] != '$' && arg[i] != ' ')
    {
        i++;
        len++;
    }
    if (len == 0)
        return (NULL);
    char *key = malloc(sizeof(char) * (len + 1));
    if (!key)
        return (NULL);
    i -= len;
    int k = 0;
    while (k < len)
    {
        key[k] = arg[i];
        k++;
        i++;
    }
    key[len] = '\0';
    return (key);
}

char *dollar_verification(char *arg)
{
    char *key;

    if (!arg)
        return (NULL);
    if (!does_dollar_exist(arg) || arg[0] == '\'')
        return (NULL);
    key = is_valid_key(arg);
    return (key);
}