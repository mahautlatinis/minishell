/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_expand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahautlatinis <mahautlatinis@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:14:31 by malatini          #+#    #+#             */
/*   Updated: 2023/10/13 16:49:55 by mahautlatin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*expand_line(char *line, t_mem *m, int i, char *temp)
{
	char	*buffer;

	buffer = (char *)malloc(sizeof(char));
	if (!buffer)
		failure(-1, m);
	buffer[0] = 0;
	while (line[i])
	{
		if (line[i] == '$' && line[i + 1] == '?')
		{
			i += 2;
			temp = ft_itoa(return_last_ret(m), m);
			buffer = copy_str_in_buf(buffer, temp, m);
			free(temp);
		}
		else if (line[i] == '$' && is_key_char_begin(line[i + 1]))
		{
			m->line = line;
			m->buffer = &buffer;
			quote_expand(m, &i);
		}
		else if (line[i++])
			buffer = copy_in_buffer(buffer, line[i - 1], m);
	}
	return (buffer);
}

int	append_env_var(char *v, char *old_value, t_mem *m, t_env_elem *e)
{
	int		total_len;
	char	*new_value;
	int		len;
	int		j;

	new_value = NULL;
	j = 0;
	len = ft_strlen(old_value);
	total_len = ft_strlen(old_value) + ft_strlen(v);
	new_value = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!new_value)
		failure(-1, m);
	ft_strcpy(new_value, old_value);
	while (len < total_len)
	{
		new_value[len] = v[j];
		j++;
		len++;
	}
	new_value[len] = '\0';
	free(e->value);
	e->value = NULL;
	e->value = new_value;
	return (0);
}

int	add_key_no_value(char *str, t_mem *mem)
{
	int			ret;
	t_env_elem	*last;
	t_env_elem	*tmp;

	if (find_key_in_env(str, mem))
		return (0);
	ret = 0;
	last = (t_env_elem *)malloc(sizeof(t_env_elem));
	if (!last)
		exit (EXIT_FAILURE);
	last->key = ft_strdup(str, mem);
	last->value = NULL;
	last->next = NULL;
	last->display = NULL;
	tmp = mem->env_list->first;
	if (!tmp)
	{
		mem->env_list->first = last;
		return (1);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = last;
	return (ret);
}

void	set_exp(t_mem *m)
{
	m->exp->i = 1;
	m->exp->old_value = NULL;
	m->exp->append = NULL;
	m->exp->key = NULL;
	m->exp->env_elem = NULL;
	return ;
}

bool	check_key(char *str, t_mem *mem)
{
	int		i;

	i = 0;
	if (!str[i] || (!ft_isalpha(str[i]) && str[i] != '_'))
	{
		d5_err_p_ret("\': not a valid identifier\n", str, mem, 1);
		return (false);
	}
	i++;
	if (str[i] == '+' || str[i] == '=')
	{
		d5_err_p_ret("\': not a valid identifier\n", str, mem, 1);
		return (false);
	}
	while (str[i] && str[i] != '+' && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
		{
			fprintf(stderr, "%c\n", str[i]);
			d5_err_p_ret("\': not a valid identifier\n", str, mem, 1);
			return (false);
		}
		i++;
	}
	return (true);
}