/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahautlatinis <mahautlatinis@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 21:43:48 by malatini          #+#    #+#             */
/*   Updated: 2023/10/13 15:36:23 by mahautlatin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	end_heredoc(int pid, t_file_elem *f, int *heredoc_pipe)
{
	int	ret;

	g_sig_var.heredoc = false;
	waitpid(pid, &ret, 0);
	signal(SIGQUIT, &s_quit);
	ret = WEXITSTATUS(ret);
	f->fd = heredoc_pipe[0];
	if (ret == 0)
	{
		close(heredoc_pipe[1]);
		return (1);
	}
	close(heredoc_pipe[1]);
	return (0);
}

void	loop_heredoc(char *line, t_mem *mem, t_file_elem *f, int *heredoc_pipe)
{
	char	*temp;

	while (true)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("bash: avertissement : « here-document »\n", 2);
			break ;
		}
		if (!ft_strcmp(line, f->path))
		{
			free(line);
			break ;
		}
		if (!f->quotes)
		{
			temp = line;
			line = expand_line(line, mem, 0, NULL);
			free(temp);
		}
		write(heredoc_pipe[1], line, ft_strlen(line));
		write(heredoc_pipe[1], "\n", 1);
		free(line);
	}
	return ;
}

int	ft_heredoc(t_file_elem *f, t_cmd_elem *elem, t_mem *mem)
{
	int		pid;
	int		heredoc_pipe[2];
	char	*line;

	(void)elem;
	line = NULL;
	pipe(heredoc_pipe);
	signal(SIGQUIT, &s_quit_hd);
	g_sig_var.heredoc = true;
	pid = fork();
	g_sig_var.pid = pid;
	if (pid == 0)
	{
		loop_heredoc(line, mem, f, heredoc_pipe);
		close(heredoc_pipe[1]);
		exit (1);
	}
	return (end_heredoc(pid, f, heredoc_pipe));
}
