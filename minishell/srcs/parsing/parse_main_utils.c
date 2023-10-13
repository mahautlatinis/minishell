/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahautlatinis <mahautlatinis@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 17:55:44 by malatini          #+#    #+#             */
/*   Updated: 2023/10/13 15:38:39 by mahautlatin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	check_parsing_end_conditions(t_cmd_elem *elem, t_mem *mem, int *ret)
{
	(void)elem;
	*ret = 1;
	if (check_cmd(mem->cmd) == -1)
	{
		ft_putstr_fd("Parse error.\n", 2);
		push_ret_elem(mem, 2);
		*ret = -1;
	}
	if (check_file(mem) < 0)
		*ret = -1;
	if (*(mem->buffer))
		free(*(mem->buffer));
	return (*ret);
}

int	handle_pipe(t_mem *m, t_parse *p)
{
	if (p->r_type != R_NONE)
	{
		ft_putstr_fd("Issue with a pipe.\n", 2);
		failure(EXIT_FAILURE, m);
	}
	end_arg(m->buffer, p->e, m, &p->r_type);
	p->e->is_piped = true;
	p->e = push_cmd(m->cmd, m);
	p->i++;
	return (0);
}

int	handle_redir(t_mem *m, t_parse *p)
{
	if (p->r_type != R_NONE)
	{
		p->error = true;
		return (-1);
	}
	end_arg(m->buffer, p->e, m, &p->r_type);
	p->r_type = set_redir_type(m->line, p->i, p->e, m);
	if (p->r_type < 0)
		return (-1);
	if (p->r_type == RR_INPUT || p->r_type == RR_OUTPUT)
		p->i++;
	p->i++;
	return (0);
}

int	check_file(t_mem *mem)
{
	t_cmd_elem	*elem;
	t_file_elem	*file_elem;

	elem = mem->cmd->first;
	while (elem)
	{
		file_elem = elem->file->first;
		if (elem->redir_type != R_NONE && !file_elem)
		{
			ft_putstr_fd("minishell: parse error\n", 2);
			push_ret_elem(mem, 1);
			return (-1);
		}
		else if (elem->redir_type != R_NONE && !ft_strcmp(file_elem->path, ""))
		{
			ft_putstr_fd("bash: No such file or directory\n", 2);
			push_ret_elem(mem, 127);
			return (-2);
		}
		elem = elem->next;
	}
	return (0);
}
