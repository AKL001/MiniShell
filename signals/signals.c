#include "../includes/header.h"

void	sigint_handler(int sig)
{
	(void)sig;
    if (g_vars.in_child == 0)
    {
        write(1, "\n", 1);
        rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}

void	setup_parent_signals(void)
{
	signal(SIGINT, sigint_handler);  
	signal(SIGQUIT, SIG_IGN);        
}

void   handle_child_signals(int sig_num)
{
    if (sig_num == 2)
        g_vars.g_exit_status = 130;
    else
    {
        ft_putstr_fd("Quit", 1);
        g_vars.g_exit_status = 131;
    }
    write(1, "\n",1);
}

void	setup_child_signals(void)
{
	signal(SIGINT, SIG_DFL);  
	signal(SIGQUIT, SIG_DFL);
}
