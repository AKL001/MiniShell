#include  "../includes/header.h"

int	read_heredoc(t_redir *heredoc, int *heredoc_fd)
{
	char	*line;
	char	temp_filename[] = ".heredoc_temp";
	int		temp_fd;
	char	*delimiter;

	delimiter = heredoc->filename;
	temp_fd = open(temp_filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (temp_fd == -1)
		return (error_message("heredoc temp file", 1));

	while (1)
	{
		write(STDOUT_FILENO, "> ", 2);
		line = ft_read_until_newline(STDIN_FILENO);
		if (!line)
			break;
		
		// Trim newline and compare
		if (line[ft_strlen(line)-1] == '\n')
			line[ft_strlen(line)-1] = '\0';
		
		if (ft_strcmp(line, delimiter) == 0)
		{
			free(line);
			break;
		}
		
		// Restore newline for writing
		write(temp_fd, line, ft_strlen(line));
		write(temp_fd, "\n", 1);
		free(line);
	}
	close(temp_fd);
	
	// Open for reading and clean up
	*heredoc_fd = open(temp_filename, O_RDONLY);
	unlink(temp_filename);
	if (*heredoc_fd == -1)
		return (error_message("heredoc read", 1));
	return (0);
}


