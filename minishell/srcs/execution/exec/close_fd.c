/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malatini <malatini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 12:28:10 by malatini          #+#    #+#             */
/*   Updated: 2021/09/30 18:21:14 by malatini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 ** Va boucler sur tous les pipes des commandes pour les close
 * @author: malatini
 */
int	ft_close_pipes(t_mem *mem)
{
	int			ret;
	t_cmd_elem	*cmd_elem;

	cmd_elem = mem->cmd->first;
	while (cmd_elem)
	{
		if (cmd_elem->is_piped)
		{
			close(cmd_elem->pipe[0]);
			close(cmd_elem->pipe[1]);
		}
		cmd_elem = cmd_elem->next;
	}
	ret = 0;
	return (ret);
}

/**
 ** Va boucler sur tous les fds des commandes pour les close
 * @author: malatini
 */
int	close_all_fds(t_mem *mem)
{
	t_cmd_elem	*cmd_elem;
	t_file_elem	*file_elem;
	int			ret;

	ret = -1;
	cmd_elem = mem->cmd->first;
	while (cmd_elem)
	{
		file_elem = cmd_elem->file->first;
		while (file_elem)
		{
			close(file_elem->fd);
			file_elem = file_elem->next;
		}
		cmd_elem = cmd_elem->next;
	}
	return (ret);
}
