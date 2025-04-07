/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-aiss <ael-aiss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 03:32:11 by ael-aiss          #+#    #+#             */
/*   Updated: 2025/03/24 23:31:12 by ael-aiss         ###   ########.fr       */
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
#include <sched.h>
#include <fcntl.h>
#include <sys/wait.h>


#define RED   "\033[31m"
#define RESET "\033[0m"

typedef struct s_vars{

	int g_exit_status;

} 				t_vars;

extern t_vars g_vars;


typedef struct s_gc_node {
    void *ptr;
    struct s_gc_node *next;
} 				t_gc_node;

typedef struct s_gc {
    t_gc_node *allocations;
} 					t_gc;


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
	int             heredoc_fd;
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
t_command			*parse_token(t_token *token, t_env *custom_env);

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


/*****************SYNTAX ERROR*****************/
int syntax_checker(char *input);
int	is_valid_redirection(char *input, int i);
int	check_redir_follow(char *input, int i);
int	check_op_at_end(char *input, int i);
int	check_operator(char *input, int *i, char op);
int is_valid_operator(char *input, int i, char set);
void handle_q_type(char *input,int i,char *q_type);
char	*skip_spaces(char *input);


/***************redirections.c*****************/
int					is_redirection(t_token_type token_type);
t_redir_type		get_redirection_type(t_token_type token_type);

//**************print cmd**************************
void				print_commands(t_command *cmd);

// ******************expantion**********************
char				*get_var_value(t_env *custom_env, char *key);
void				variable_expansion(t_command *command ,t_env *custom_env);
int					is_escaped(char *arg);
char				*is_valid_key(char *arg);
char				*dollar_verification(char *arg);
void				assign_variable_value(char **dollar_value, char *key, t_env *custom_env);
char				*retrieve_variable_value(t_env *custom_env, char *key);

// ******************expantion**********************
void				remove_quotes(t_command *cmd);

// built_in functions : 
t_env *init_envp(char **envp);
// int execute_builtin(t_env *my_envp, char **args);

int	execute_builtin(t_command *cmd, t_env **env);


void my_export(t_env *my_envp, char **args);
void my_unset(t_env *my_envp, char **args);
int my_echo(t_env *my_envp, char **args);
void my_pwd(char **args);
void my_env(t_env *custom_env);
void my_cd(char **args); 

/*  execution  */

int	execute_command_line(t_command *cmd, t_env *env);
char	*ft_strjoin_three(char *s1, char *s2, char *s3);
char	*get_env_value(char *key, t_env *env);
char	*find_command_path(char *cmd, t_env *env);
int	error_message(char *msg, int status);
char	**args_to_array(t_args *args);

char	**env_to_array(t_env *env);
void	free_array(char **arr);
int	ft_strcmp(const char *s1, const char *s2);
int	handle_redirections(t_command *cmd);
int	execute_pipeline(t_command *cmd, t_env *env);
// int setup_pipes_with_heredoc(t_command *cmd, int input_fd, t_env *env, pid_t *child_pids, int *pid_count);
// int execute_command_line_with_heredoc(t_command *cmd, t_env *env);

/* herdoc_UTILS */

char	*ft_read_until_newline(int fd);
int	read_heredoc(t_redir *heredoc, int *heredoc_fd);
int	handle_heredocs(t_command *cmd);
int	get_next_line(char *delimiter, int heredoc_fd);
void	cleanup_heredocs(t_command *cmd);
