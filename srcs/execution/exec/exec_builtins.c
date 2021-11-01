/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malatini <malatini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 16:08:10 by malatini          #+#    #+#             */
/*   Updated: 2021/09/30 18:08:41 by malatini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
** Appelle l'execution du builtin
* @author: malatini
*/
int	exec_build(t_cmd_elem *elem, t_mem *mem)
{
	push_ret_elem(mem, 0);
	if (elem->args && !ft_strcmp(elem->args[0], "cd"))
		return (ft_exec_cd(elem, mem));
	if (elem->args && !ft_strcmp(elem->args[0], "echo"))
		return (ft_exec_echo(elem, mem));
	else if (elem->args && !ft_strcmp(elem->args[0], "unset"))
		return (ft_exec_unset(elem, mem));
	else if (elem->args && !ft_strcmp(elem->args[0], "export"))
		return (ft_exec_export(elem, mem));
	else if (elem->args && !ft_strcmp(elem->args[0], "pwd"))
		return (ft_exec_pwd(mem));
	else if (elem->args && !ft_strcmp(elem->args[0], "env"))
		return (ft_exec_env(mem->env_list, mem));
	else if (elem->args && !ft_strcmp(elem->args[0], "exit"))
		return (ft_exec_exit(elem, mem));
	else
		return (0);
}
