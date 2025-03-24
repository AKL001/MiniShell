/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 03:32:11 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/03/24 07:10:06 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include <limits.h>
#include <math.h>
#include <readline/history.h>
#include <readline/readline.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

typedef enum s_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIRECT_IN,
	TOKEN_REDIRECT_OUT,
	TOKEN_APPEND,
	TOKEN_HEREDOC,
}					t_token_type;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_APPEND,
	REDIR_HEREDOC
}					t_redir_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}					t_token;

typedef struct s_redir
{
	t_redir_type	type;
	char			*filename;
	struct s_redir	*next;
}					t_redir;

typedef struct s_args
{
	char			*value;
	struct s_args	*next;
}					t_args;

typedef struct s_cmd
{
	t_args			*args;
	t_redir			*redirections;
	struct s_cmd	*next;
}					t_command;



typedef struct s_env
{
    char *key;
    char *value;
    struct s_env *next;
} t_env;



// lexing*********************************
t_token				*create_new_token(char *value);
void				add_new_token(t_token **tokens, char *value);
t_token				*tokenazation(char *input);
t_token_type		set_type_token(char *value);
char				*trim_whitespace(char *input);
int					check_unclosed_quotes(char *cmd);
void				free_token(t_token *tokens);
t_token				*command_to_tokens(char *cmd);
int					is_operator(char c);
char				*handle_quote(char *cmd, int *i);
char				*handle_operator(char *cmd, int *i);
int					is_op_or_quote(char c);
int					is_space_or_tab(char c);
int					is_quote(char c);
/*******************ft_split.c*****************/
void				free_strings(char **strings);
void				print_tokens(t_token *token);
char				**ft_split_plus(char *str, char *sep);
/*******************handle_word.c*****************/
char				*handle_word(char *cmd, int *i);
int					inside_quotes(char *str);
int					count_number_of_strings(char **strings);
void				add_strings_to_token(char **words, t_token **token);
void				split_wordes(t_token **token);

/***************parsing*********************/
t_command			*parse_token(char *cmd, t_env *custom_env);

/**************parse_utils******************/
void				add_command_redirection(t_command *cmd, t_redir_type type,
						char *filename);
void				add_command_args(t_command *cmd, char *value);
t_command			*create_command(void);
int					is_redirection(t_token_type token_type);
t_redir_type		get_redirection_type(t_token_type token_type);

/***************cleanup**********************/
void				free_commands(t_command *cmd);
void				free_args(t_args *args);
void				free_redir(t_redir *redir);

/***************redirections.c*****************/
int					is_redirection(t_token_type token_type);
t_redir_type		get_redirection_type(t_token_type token_type);

//print cmd :
void				print_commands(t_command *cmd);

// ******************expantion**********************
char				*get_var_value(t_env *custom_env, char *key);
void				variable_expansion(t_command *command ,t_env *custom_env);
int					is_escaped(char *arg);
char				*is_valid_key(char *arg);
char				*dollar_verification(char *arg);
void				assign_variable_value(char **dollar_value, char *key, t_env *custom_env);
char				*retrieve_variable_value(t_env *custom_env, char *key);

// built_in functions : 

t_env *init_envp(char **envp);
int execute_builtin(t_env *my_envp, char **args);
void my_export(t_env *my_envp, char **args);
void my_unset(t_env *my_envp, char **args);
int my_echo(t_env *my_envp, char **args);
void my_pwd(char **args);
void my_env(t_env *custom_env);