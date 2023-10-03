/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malatini <malatini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 14:40:47 by user42            #+#    #+#             */
/*   Updated: 2021/09/29 17:24:04 by malatini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	syntax_error(t_mem *mem)
{
	t_cmd_elem	*elem;
	int			ret;

	ret = 0;
	elem = mem->cmd->first;
	while (elem)
	{
		if ((elem->redir_type != R_NONE && !elem->file->first->path)
			|| (elem->redir_type < 0))
		{
			ft_putstr_fd("minishell: syntax error.\n", 2);
			push_ret_elem(mem, 2);
			ret = -1;
		}
		elem = elem->next;
	}
	return (ret);
}
