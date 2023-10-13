/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahautlatinis <mahautlatinis@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:57:48 by malatini          #+#    #+#             */
/*   Updated: 2023/10/13 15:31:56 by mahautlatin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	append_env_var(char *v, char *old_value, t_mem *m, t_env_elem *e)
{
	int		total_len;
	char	*new_value;
	int		len;
	int		j;

	(void)m;
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

void	set_exp(t_cmd_elem *el, t_mem *m)
{
	(void)el;
	m->exp->i = 1;
	m->exp->old_value = NULL;
	m->exp->append = NULL;
	m->exp->key = NULL;
	m->exp->env_elem = NULL;
	return ;
}
