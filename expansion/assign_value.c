/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   assign_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 08:42:58 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/03/22 23:52:53 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

void assign_variable_value(char **dollar_value, char *key, t_env *custom_env)
{
    char *value = retrieve_variable_value(custom_env, key);
    char *new_value;
    char *new_value2;
    char *after_dollar;
    if (!value)
        value = ft_strdup("");
    char *value_ptr = *dollar_value;

    int i = 0;
    while (value_ptr[i] && value_ptr[i] != '$')
        i++;
    if (value_ptr[i] == '$')
    {
        after_dollar = value_ptr + i + 1 + ft_strlen(key);
        value_ptr[i] = '\0';
        new_value = ft_strjoin(value_ptr, value);
        new_value2 = ft_strjoin(new_value, after_dollar);
        free(new_value);
        free(value);
        *dollar_value = new_value2;
        free(value_ptr);
    }
    else
        free(value);
}
