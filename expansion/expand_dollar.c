/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 17:16:31 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/10 17:16:40 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

static char *handle_special_cases(const char *s, int *i)
{
    if (s[*i] == '$')
    {
        (*i)++;
        return (ft_itoa(getpid()));
    }
    if (s[*i] == '?')
    {
        (*i)++;
        return (ft_itoa(g_vars.g_exit_status));
    }
    if (s[*i] == '$' || s[*i] == ' ')
    {
        return (ft_strdup("$"));
    }
    return (NULL);
}

static char *handle_regular_variable(const char *s, int *i, t_env *env)
{
    int start = *i;
    char *key;
    char *val;

    while (s[*i] && ft_isalnum(s[*i]))
        (*i)++;
    key = ft_substr(s, start, *i - start);
    if (!key)
        return (NULL);
    val = get_env_value_2(key, env);
    free(key);
    return (val);
}

char *expand_dollar(const char *s, int *i, t_env *env)
{
    int start;
    char *result;

    if (!s)
        return (ft_strdup(""));
    (*i)++;
    start = *i;
    if (!s[*i] || s[*i] == '"')
        return (ft_strdup("$"));
    result = handle_special_cases(s, i);
    if (result)
        return (result);
    return (handle_regular_variable(s, i, env));
}