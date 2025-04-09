#include "../includes/header.h"

static int	handle_input_redir(t_redir *redir, int *first_in)
{
	if (*first_in != -1)
		return (0);
	*first_in = open(redir->filename, O_RDONLY);
	if (*first_in == -1)
		return (error_message(redir->filename, 1));
	return (0);
}

static int	handle_output_redir(t_redir *redir, int *first_out)
{
	int	fd;
	int	flags;

	flags = O_WRONLY | O_CREAT;
	if (redir->type == REDIR_OUT)
		flags |= O_TRUNC;
	else
		flags |= O_APPEND;
	fd = open(redir->filename, flags, 0644);
	if (fd == -1)
		return (error_message(redir->filename, 1));
	if (*first_out == -1)
		*first_out = fd;
	else
		close(fd);
	return (0);
}

static int process_input_redirs(t_command *cmd, int *in_fd, int *last_input_type)
{
    t_redir *r = cmd->redirections;

    while (r)
    {
        if (r->type == REDIR_IN && !(*last_input_type))
        {
            if (*in_fd != -1)
                close(*in_fd);
            if (handle_input_redir(r, in_fd) == -1)
                return (-1);
            *last_input_type = 1;
        }
        else if (r->type == REDIR_HEREDOC && !(*last_input_type))
        {
            if (*in_fd != -1)
                close(*in_fd);
            *in_fd = r->heredoc_fd;
            *last_input_type = 1;
        }
        r = r->next;
    }
    return (0);
}

static int process_output_redirs(t_command *cmd, int *out_fd)
{
    t_redir *r = cmd->redirections;

    while (r)
    {
        if (r->type == REDIR_OUT || r->type == REDIR_APPEND)
        {
            if (handle_output_redir(r, out_fd) == -1)
                return (-1);
        }
        r = r->next;
    }
    return (0);
}

int handle_redirections(t_command *cmd)
{
    int in_fd = -1;
    int out_fd = -1;
    int last_input_type = 0;

    if (process_input_redirs(cmd, &in_fd, &last_input_type) == -1)
        return (-1);
    if (process_output_redirs(cmd, &out_fd) == -1)
        return (-1);
    if (in_fd != -1 && (dup2(in_fd, STDIN_FILENO) == -1 || close(in_fd) == -1))
        return (-1);
    if (out_fd != -1 && (dup2(out_fd, STDOUT_FILENO) == -1 || close(out_fd) == -1))
        return (-1);
    return (0);
}


// int handle_redirections(t_command *cmd)
// {
//     t_redir *r = cmd->redirections;
//     int in_fd = -1;
//     int out_fd = -1;
//     int last_input_type = 0;

//     r = cmd->redirections;
//     while (r)
//     {
//         if (r->type == REDIR_IN && !last_input_type)
//         {
//             if (in_fd != -1)
//                 close(in_fd);
//             if (handle_input_redir(r, &in_fd) == -1)
//                 return (-1);
//             last_input_type = 1;
//         }
//         else if (r->type == REDIR_HEREDOC && !last_input_type)
//         {
//             if (in_fd != -1)
//                 close(in_fd);
//             in_fd = r->heredoc_fd;
//             last_input_type = 1;
//         }
//         r = r->next;
//     }
//     r = cmd->redirections;
//     while (r)
//     {
//         if (r->type == REDIR_OUT || r->type == REDIR_APPEND)
//         {
//             if (handle_output_redir(r, &out_fd) == -1)
//                 return (-1);
//         }
//         r = r->next;
//     }
//     if (in_fd != -1)
//         if (dup2(in_fd, STDIN_FILENO) == -1 || close(in_fd) == -1)
//             return (-1);
//     if (out_fd != -1)
//         if (dup2(out_fd, STDOUT_FILENO) == -1 || close(out_fd) == -1)
//             return (-1);
    
//     return 0;
// }

