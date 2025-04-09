/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 23:05:16 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/09 11:32:20 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/header.h"

int is_quoted(char *argument)
{
    if (!argument || !*argument)
        return (0);
    int len = ft_strlen(argument);
    if (len >= 2 && is_quote(argument[0]) && argument[len - 1] == argument[0])
        return (1);
    else
        return (0);
}

// void remove_quotes(t_command *cmd)
// {
//     char *string;
//     char *new_string;
//     t_args *args;
//     t_command *head;
//     int len;

//     if (!cmd)
//         return;
//     head = cmd;
//     while (head)
//     {
//         args = head->args;   
//         while (args)
//         {
//             string = args->value;
//             if (is_quoted(string))
//             {
//                 len = ft_strlen(string);
//                 new_string = ft_substr(string, 1, len - 2);
//                 if (new_string)
//                 {
//                     args->value = new_string;
//                     free(string);
//                 }
//             }
//             args = args->next;
//         }
//         head = head->next;
//     }
// }
