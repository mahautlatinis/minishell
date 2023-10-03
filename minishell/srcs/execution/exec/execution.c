/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malatini <malatini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 16:04:00 by malatini          #+#    #+#             */
/*   Updated: 2021/09/30 18:24:36 by malatini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
** Function qui porte mal son nom. Fork, realise l'execution.
** Ne fork pas s'il s'agit d'un builtin.
* @author: malatini
*/
int	exec_no_builtin(t_cmd_elem *elem, t_mem *mem)
{
	bool		is_piped;
	t_cmd_elem	*prev_piped;

	is_piped = setup_builtin_pipe(elem, mem, &prev_piped);
	if (elem->redir_type != R_NONE && ft_redirection(elem, mem) == -1)
		return (close_all_fds(mem));
	elem->pid = 0;
	if ((prev_piped || elem->is_piped) || (!elem->is_builtin && elem->path))
	{
		elem->pid = fork();
		elem->is_forked = true;
	}
	g_sig_var.pid = elem->pid;
	if (elem->pid == 0)
		child_function(elem, mem, prev_piped);
	if (prev_piped)
		close(prev_piped->pipe[0]);
	if (is_piped)
	{
		close(elem->pipe[1]);
		if (!elem->next)
			close(elem->pipe[0]);
	}
	return (0);
}

/**
** Va generer des messages d'erreurs (ou pas)
** Et verifier si le PATH est set et que la commande n'est pas un chemin
* @author: malatini
*/
int	loop_for_execution(t_cmd_elem *e, t_mem *m, int *ret)
{
	while (e)
	{
		e->path = find_exec(e, m);
		if (!e->path && (e->args && ft_strchr(e->args[0], '/')))
			return (-1);
		m->found = !e->args || e->path || e->args[0][0] == '/'
			|| e->args[0][0] == '.' || is_builtin(e->args[0]);
		if (!m->found)
			e->is_piped = false;
		if (exec_no_builtin(e, m) == -1)
			break ;
		if (!m->found)
		{
			if ((!e->path || e->path[0] != '/' || e->path[0] != '.')
				&& (e->args && !is_builtin(e->args[0])))
				d2_err_p_ret(": command not found\n", e->args[0], m, 127);
			else if (e->path_set == false && !is_builtin(e->args[0]))
				d3_err(": No such file or directory\n", e->args[0], m, 1);
		}
		e = e->next;
	}
	return (*ret);
}

/**
** Fonction principale pour l'execution
* @author: malatini
*/
int	ft_execution(t_mem *mem)
{
	int			ret;
	t_cmd_elem	*elem;

	ret = 0;
	check_path_set(mem);
	elem = mem->cmd->first;
	loop_for_execution(elem, mem, &ret);
	ft_close_pipes(mem);
	close_all_fds(mem);
	ret = wait_exec_cmds(mem->cmd->first, mem);
	loop_through_env_var(mem);
	return (ret);
}

bool	is_file(char *path)
{
	struct stat	path_stat;

	if (!path)
		return (true);
	stat(path, &path_stat);
	return (S_ISREG(path_stat.st_mode));
}
