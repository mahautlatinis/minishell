/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahautlatinis <mahautlatinis@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 19:43:51 by malatini          #+#    #+#             */
/*   Updated: 2023/10/13 16:54:44 by mahautlatin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*read_quoted(t_mem *m, int *pos, t_parse *p)
{
	char	quote;
	char	*temp;

	m->quotes = true;
	quote = m->line[*pos];
	(*pos)++;
	while (m->line[*pos] && m->line[*pos] != quote)
	{
		if (quote == '"' && m->line[p->i] == '$' && m->line[p->i + 1] == '?')
		{
			p->i += 2;
			temp = ft_itoa(return_last_ret(m), m);
			*(m->buffer) = copy_str_in_buf((*m->buffer), temp, m);
			free(temp);
		}
		else if (m->line[*pos] == '$' && quote == '"'
			&& is_key_char_begin(m->line[p->i + 1]))
			quote_expand(m, pos);
		else
			*(m->buffer) = copy_in_buffer(*(m->buffer), m->line[(*pos)++], m);
	}
	if (!m->line[*pos])
		p->error = true;
	return (*(m->buffer));
}

char	**add_str_to_tab(t_cmd_elem *elem, char *buffer, t_mem *mem)
{
	int		len;
	char	**new;
	int		i;

	if (!elem && !buffer)
		return (NULL);
	i = 0;
	new = NULL;
	len = elem->args_len;
	new = (char **)malloc(sizeof(char *) * (len + 2));
	if (!new)
		failure(-1, mem);
	while (i < len)
	{
		new[i] = elem->args[i];
		i++;
	}
	new[i++] = buffer;
	new[i] = NULL;
	if (elem->args)
		free(elem->args);
	elem->args = new;
	return (new);
}

void	reinitialize_buffer(char **buffer)
{
	*buffer = NULL;
	return ;
}

t_cmd_elem	*push_cmd(t_cmd *cmd, t_mem *mem)
{
	t_cmd_elem	*new;
	t_cmd_elem	*tmp;

	new = (t_cmd_elem *)malloc(sizeof(t_cmd_elem));
	if (!new)
		failure(-1, mem);
	new->args = NULL;
	new->args_len = 0;
	new->pid = 0;
	new->next = NULL;
	new->is_piped = false;
	new->redir_type = R_NONE;
	new->path = NULL;
	new->path_set = true;
	new->file = (t_file_list *)malloc(sizeof(t_file_list));
	if (!new)
		failure(-1, mem);
	new->file->first = NULL;
	new->is_forked = false;
	tmp = cmd->first;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (new);
}

void	end_arg(char **buffer, t_cmd_elem *elem, t_mem *mem, enum e_r *type)
{
	if (!(*buffer))
		return ;
	if (*type != R_NONE)
		push_file_elem(elem, buffer, mem->quotes, *type);
	else
	{
		add_str_to_tab(elem, *buffer, mem);
		elem->args_len++;
	}
	mem->quotes = false;
	reinitialize_buffer(buffer);
	*type = R_NONE;
	return ;
}
