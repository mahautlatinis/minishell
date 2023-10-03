/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 16:06:30 by malatini          #+#    #+#             */
/*   Updated: 2021/09/26 18:42:45 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
** Va permettre d'ouvrir tous les fichiers
** sur lesquels on va ecrire/append
*** TODO: retester en cas d erreur si pas droits sur le fichier
***       + sous fonction pour la norme.
*/
int	redir_output_simple(t_cmd_elem *cmd, t_mem *mem)
{
	t_file_elem	*f;

	f = cmd->file->first;
	while (f)
	{
		if (f->redir_type == R_OUTPUT)
			f->fd = open(f->path, O_RDWR | O_CREAT | O_TRUNC, 0644);
		else if (f->redir_type == RR_OUTPUT)
			f->fd = open(f->path, O_CREAT | O_RDWR | O_APPEND, 0644);
		else
		{
			f = f->next;
			continue ;
		}
		if (errno == EACCES)
		{
			d3_err(": Permission denied\n", f->path, mem, 126);
			return (-1);
		}
		f = f->next;
	}
	return (0);
}

int	redir_input_simple(t_cmd_elem *elem, t_mem *mem)
{
	t_file_elem	*f;

	f = elem->file->first;
	while (f)
	{
		if (f->redir_type == R_INPUT)
		{
			f->fd = open(f->path, O_RDONLY);
			if (f->fd < 0)
			{
				ft_putstr_fd("bash: ", 2);
				ft_putstr_fd(f->path, 2);
				ft_putstr_fd(": No such file or directory\n", 2);
				push_ret_elem(mem, 127);
				return (1);
			}
		}
		else if (f->redir_type == RR_INPUT)
		{
			if (ft_heredoc(f, elem, mem))
				return (1);
		}
		f = f->next;
	}
	return (0);
}

int	ft_redirection(t_cmd_elem *elem, t_mem *mem)
{
	if (redir_input_simple(elem, mem) != 0)
		return (-1);
	if (redir_output_simple(elem, mem) != 0)
		return (-1);
	return (0);
}
