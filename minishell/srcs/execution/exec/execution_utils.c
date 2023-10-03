/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malatini <malatini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 20:22:34 by malatini          #+#    #+#             */
/*   Updated: 2021/09/30 18:27:14 by malatini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
** Verifie si la chaine de chars constitue un builtin
* @author: malatni
*/
int	is_builtin(char *s)
{
	if (s)
	{
		if (!ft_strcmp(s, "echo") || !ft_strcmp(s, "cd")
			|| !ft_strcmp(s, "pwd") || !ft_strcmp(s, "unset")
			|| !ft_strcmp(s, "export") || !ft_strcmp(s, "exit")
			|| !ft_strcmp(s, "env"))
		{
			return (true);
		}
	}
	return (false);
}

/**
** Attend que les forks soient executes. Necessaire pour les pipes !
* @author: malatini
*/
int	wait_exec_cmds(t_cmd_elem *elem, t_mem *mem)
{
	int			ret;
	int			status;
	bool		prev;

	ret = 0;
	while (elem)
	{
		prev = prev_is_piped(elem, mem->cmd) || elem->is_piped;
		if (((elem->args && !is_builtin(elem->args[0])) || prev) && elem->pid)
		{
			waitpid(elem->pid, &status, 0);
			if (WIFEXITED(status))
				ret = WEXITSTATUS(status);
			push_ret_elem(mem, ret);
		}
		elem = elem->next;
	}
	if (mem->env_test)
	{
		free_tab(mem->env_test);
		mem->env_test = NULL;
	}
	return (ret);
}

/**
** Indique si la commande precedente est pipee
* @author: malatini
*/
t_cmd_elem	*prev_is_piped(t_cmd_elem *elem, t_cmd *cmd)
{
	t_cmd_elem	*tmp;

	tmp = cmd->first;
	while (tmp->next && tmp->next != elem)
		tmp = tmp->next;
	if (tmp->is_piped && tmp->next == elem)
		return (tmp);
	return (NULL);
}

/**
* ! Deprecated
** Va permettre de fermer les pipes (sous function)
* @author: malatini
*/
int	close_prev_pipe(t_cmd_elem *elem, t_cmd *cmd)
{
	t_cmd_elem	*tmp;

	tmp = cmd->first;
	while (tmp->next != elem)
		tmp = tmp->next;
	if (tmp->next == elem && tmp->is_piped)
	{
		close(elem->pipe[0]);
		return (1);
	}
	return (-1);
}

/**
* ! Deprecated
** Va permettre de fermer les pipes
* @author: malatini
*/
int	close_pipes(t_cmd_elem *elem, int is_piped, t_cmd *cmd)
{
	if (prev_is_piped(elem, cmd))
		close_prev_pipe(elem, cmd);
	if (!is_piped)
		return (1);
	close (elem->pipe[1]);
	if (!elem->next)
		close (elem->pipe[0]);
	return (1);
}
