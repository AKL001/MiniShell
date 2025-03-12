# ifndef  MINISHELL_H
# define  MINISHELL_H

#include "../libft/libft.h"
#include "lexer.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "header.h"


// Regular text colors
#define BLACK   "\033[30m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"
#define RESET "\033[0m"

# define WHITESPACES		" \t\n"

typedef enum e_token_type
{
    T_WORD,         // Regular word/command/argument  0
    T_PIPE,         // Pipe operator '|'              1
    T_REDIR_IN,     // Input redirection '<'          2
    T_REDIR_OUT,    // Output redirection '>'         3
    T_REDIR_APPEND, // Append output redirection '>>' 4
    T_REDIR_HEREDOC,// Heredoc redirection '<<'       5
    T_AND,          // AND operator '&&'              6
    T_OR,           // OR operator '||'               7
    T_OPEN_PAREN,   // Open parenthesis '('           8
    T_CLOSE_PAREN,  // Close parenthesis ')'          9
    T_EOF           // End of input                   10
} t_token_type;

/* Token structure */
typedef struct s_token
{
    char            *value;     // The actual text/content
    t_token_type    type;       // Type of token
    struct s_token  *next;      // Pointer to the next token
} t_token;

/* PARSING */
void increament_quotes(char c,int *s_q_count,int *d_q_count);
t_token *syntax_checker_and_tokoniz(char *input);
void handle_q_type(char *input,int i,char *q_type);
// operatore utils functions
int is_valid_operator(char *input, int i, char set);
int	check_operator(char *input, int *i, char op);
int	check_op_at_end(char *input, int i);
char	*skip_spaces(char *input);
// redirecion utils functions
int	is_valid_redirection(char *input, int i);
int	check_redir_follow(char *input, int i);

/* TOKONIZER */
t_token	*new_token(t_token_type type, char *value);
void	add_token_to_list(t_token **tokens, t_token *new_token);
void handle_word(char **input, t_token **tokens);
t_token *tokeniz_input(char *input);
void	free_tokens(t_token *tokens);

// print tokens
void printf_tokenizer(t_token *tokens);


#endif