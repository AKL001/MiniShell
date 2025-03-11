

/* Token types to distinguish between different elements */
typedef enum e_token_type
{
    T_WORD,         // Regular word/command/argument
    T_PIPE,         // Pipe operator '|'
    T_REDIR_IN,     // Input redirection '<'
    T_REDIR_OUT,    // Output redirection '>'
    T_REDIR_APPEND, // Append output redirection '>>'
    T_REDIR_HEREDOC,// Heredoc redirection '<<'
    T_AND,          // AND operator '&&'
    T_OR,           // OR operator '||'
    T_OPEN_PAREN,   // Open parenthesis '('
    T_CLOSE_PAREN,  // Close parenthesis ')'
    T_EOF           // End of input
} t_token_type;

/* Token structure */
typedef struct s_token
{
    char            *value;     // The actual text/content
    t_token_type    type;       // Type of token
    struct s_token  *next;      // Pointer to the next token
} t_token;

/* Tokenizer context to track the parsing state */
typedef struct s_tokenizer
{
    char        *input;         // The input string to tokenize
    int         position;       // Current position in the input
    t_token     *head;          // Head of the token list
    t_token     *tail;          // Tail of the token list for easy append
    int         error;          // Error flag
    char        *error_msg;     // Detailed error message
} t_tokenizer;

/* Command structure for execution */
typedef struct s_command
{
    char                **args;     // Command and its arguments
    char                *cmd_path;  // Full path to the command
    struct s_redirect   *redirects; // Linked list of redirections
    struct s_command    *next;      // Next command in pipeline
    struct s_command    *prev;      // Previous command in pipeline (optional)
} t_command;

/* Redirection structure */
typedef struct s_redirect
{
    t_token_type        type;       // Type of redirection
    char                *file;      // File/string to redirect to/from
    struct s_redirect   *next;      // Next redirection
} t_redirect;