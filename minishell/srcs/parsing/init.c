/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahautlatinis <mahautlatinis@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 19:38:28 by malatini          #+#    #+#             */
/*   Updated: 2023/10/13 16:53:52 by mahautlatin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_mem	*init_mem(char **envp, bool env_set)
{
	t_mem	*mem;

	mem = (t_mem *)malloc(sizeof(t_mem));
	if (!mem)
		failure(-1, NULL);
	ft_memset(mem, 0, sizeof(t_mem));
	mem->cmd = NULL;
	mem->line = NULL;
	mem->buffer = NULL;
	if (env_set == true)
		mem->env = envp;
	else
		mem->env = NULL;
	mem->line = NULL;
	mem->ret_list = NULL;
	mem->env_test = NULL;
	return (mem);
}

void	define_mem(t_mem *mem, t_cmd *cmd, char *line, char **buffer)
{
	mem->cmd = cmd;
	mem->buffer = buffer;
	mem->line = line;
	return ;
}

t_cmd	*init_cmd(t_mem *mem)
{
	t_cmd	*cmd;

	cmd = NULL;
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		failure(-1, mem);
	cmd->first = NULL;
	return (cmd);
}

t_cmd_elem	*init_cmd_elem(t_cmd *cmd, t_mem *mem)
{
	t_cmd_elem	*elem;

	elem = (t_cmd_elem *)malloc(sizeof(t_cmd_elem));
	if (!elem)
		failure(-1, mem);
	ft_memset(elem, 0, sizeof(t_cmd_elem));
	elem->is_piped = false;
	elem->args_len = 0;
	elem->args = NULL;
	elem->next = NULL;
	elem->redir_type = R_NONE;
	elem->file = (t_file_list *)malloc(sizeof(t_file_list));
	if (!elem->file)
		failure(-1, mem);
	elem->file->first = NULL;
	elem->is_piped = false;
	elem->path = NULL;
	cmd->first = elem;
	return (elem);
}
