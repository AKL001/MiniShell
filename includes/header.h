/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 03:32:11 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/04/11 12:08:58 by ael-aiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

# define RED "\033[31m"
# define RESET "\033[0m"

typedef struct s_vars
{
	int				g_exit_status;
	int				in_child;
}					t_vars;

extern t_vars		g_vars;

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

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

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
	int				quoted;
	int				heredoc_fd;
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
	t_env			*env;
	struct s_cmd	*next;
}					t_command;

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
int					is_separator(char *sep, char c);
int					count_words(char *input, char *separator);
int					len_word(char *str, char *sep);
char				*word_allocation(char *str, char *sep);

/*******************handle_word.c*****************/
char				*handle_word(char *cmd, int *i);
int					inside_quotes(char *str);
int					count_number_of_strings(char **strings);
void				add_strings_to_token(char **words, t_token **token);
void				split_wordes(t_token **token);

/***************parsing*********************/
t_command			*parse_token(t_token *token, t_env *custom_env);
char				*ft_strndup(const char *s, size_t n);

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
void				free_env(t_env *env);

/*****************SYNTAX ERROR*****************/
int					syntax_checker(char *input);
int					is_valid_redirection(char *input, int i);
int					check_redir_follow(char *input, int i);
int					check_op_at_end(char *input, int i);
int					check_operator(char *input, int *i, char op);
int					is_valid_operator(char *input, int i, char set);
void				handle_q_type(char *input, int i, char *q_type);
char				*skip_spaces(char *input);

/***************redirections.c*****************/
int					is_redirection(t_token_type token_type);
t_redir_type		get_redirection_type(t_token_type token_type);

//**************print cmd**************************
/*
void				print_commands(t_command *cmd);
*/
// ******************expantion**********************
char				*ft_strjoin_free(char *s1, char *s2);
char				*get_env_value_2(char *key, t_env *env);
char				*expand_dollar(const char *s, int *i, t_env *env);
char				*handle_single_quote(const char *s, int *i);
char				*handle_double_quote(const char *s, int *i, t_env *env);
char				*expand_string(const char *s, t_env *env);
void				variable_expansion(t_command *command, t_env *custom_env);

//*******************built_in functions*************
t_env				*init_envp(char **envp);

int					execute_builtin(t_command *cmd, t_env **env);
int					count_char(char *str, char c);
void				my_export(t_env **env, char **args);
int					my_echo(t_env *my_envp, char **args);
// void				my_pwd(char **args);
void				my_pwd(t_env *env);
void				my_env(t_env *custom_env);
void				my_unset(t_env **env, char **args);
void				my_exit(char **args);
void				my_cd(char **args, t_env **env);
t_env				*create_new(char *key, char *value);
int					is_valid_identifier(char *str);
void				print_export(t_env *env);
/*  execution  */

int					execute_command_line(t_command *cmd, t_env *env);
char				*ft_strjoin_three(char *s1, char *s2, char *s3);
char				*get_env_value(char *key, t_env *env);
char				*find_command_path(char *cmd, t_env *env);
int					error_message(char *msg, int status);
char				**args_to_array(t_args *args);
char				**env_to_array(t_env *env);
void				free_array(char **arr);
int					ft_strcmp(const char *s1, const char *s2);
int					handle_redirections(t_command *cmd);
int					execute_pipeline(t_command *cmd, t_env *env);

/* herdoc_UTILS */

char				*ft_read_until_newline(int fd);
int					handle_heredocs(t_command *cmd);
int					get_next_line(char *delimiter, int heredoc_fd);
void				cleanup_heredocs(t_command *cmd);
int					read_heredoc(t_redir *heredoc, int *heredoc_fd, int open_fd,
						t_env *env);
int					execute_command(t_command *cmd, t_env *env);
int					exec_single_cmd(t_command *cmd, pid_t *pids, int *count);
int					setup_pipes(t_command *cmd, int in_fd, pid_t *pids,
						int *count);

/* signals */
void				sigint_handler(int sig);
void				setup_parent_signals(void);
void				setup_child_signals(void);

#endif