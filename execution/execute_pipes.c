#include "../includes/header.h"


static int	count_commands(t_command *cmd)
{
    int			count;
    t_command	*temp;

    count = 0;
    temp = cmd;
    while (temp)
    {
        count++;
        temp = temp->next;
    }
    return (count);
}

static int	create_pipes(int pipefds[][2], int num_pipes)
{
    int			i;

    i = 0;
    while (i < num_pipes)
    {
        if (pipe(pipefds[i]) == -1)
            return (error_message("pipe", 1));
        i++;
    }
    return (0);
}

static void	setup_io(int i, int num_commands, int pipefds[][2])
{
    int			j;

    if (i != 0)
        dup2(pipefds[i - 1][0], STDIN_FILENO);
    if (i != num_commands - 1)
        dup2(pipefds[i][1], STDOUT_FILENO);
    j = 0;
    while (j < num_commands - 1)
    {
        close(pipefds[j][0]);
        close(pipefds[j][1]);
        j++;
    }
}

static int	fork_and_execute(t_command *cmd, int i, int num_commands,
                            int pipefds[][2], t_env *env)
{
    pid_t		pid;

    pid = fork();
    if (pid == -1)
        return (error_message("fork", 1));
    if (pid == 0)
    {
        setup_io(i, num_commands, pipefds);
        if (handle_redirections(cmd) == -1)
            exit(1);
        execute_command(cmd, env);
        exit(0);
    }
    return (pid);
}

int	execute_pipeline(t_command *cmd, t_env *env)
{
    int			num_commands;
    int			pipefds[1024][2];
    pid_t		pids[1024];
    int			i;
    t_command	*current;

    num_commands = count_commands(cmd);
    if (create_pipes(pipefds, num_commands - 1) != 0)
        return (1);
    i = 0;
    current = cmd;
    while (current)
    {
        pids[i] = fork_and_execute(current, i, num_commands, pipefds, env);
        current = current->next;
        i++;
    }
    i = 0;
    while (i < num_commands - 1)
    {
        close(pipefds[i][0]);
        close(pipefds[i][1]);
        i++;
    }
    i = 0;
    while (i < num_commands)
        waitpid(pids[i++], NULL, 0);
    return (g_vars.g_exit_status);
}
