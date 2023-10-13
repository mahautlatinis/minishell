/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahautlatinis <mahautlatinis@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:11:33 by malatini          #+#    #+#             */
/*   Updated: 2023/10/13 15:31:06 by mahautlatin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	len_env_list(t_mem *mem)
{
	int			len;
	t_env_elem	*elem;

	len = 0;
	elem = mem->env_list->first;
	while (elem)
	{
		elem = elem->next;
		len++;
	}
	return (len);
}

t_env_list	*cpy_env_list(t_mem *m)
{
	t_env_list	*cpy;
	t_env_elem	*t;

	cpy = NULL;
	if (len_env_list(m))
	{
		cpy = (t_env_list *)malloc(sizeof(t_env_list));
		if (!cpy)
			failure(-1, m);
		t = m->env_list->first;
		cpy->first = NULL;
		m->temp = cpy;
		while (t)
		{
			m->no_display_temp = t->display;
			push_env_var(ft_strdup(t->key, m),
				ft_strdup(t->value, m), m, false);
			t = t->next;
		}
	}
	return (cpy);
}

t_env_list	*bubble_swap_key(t_env_elem *e, t_env_elem *n, t_env_list *cpy)
{
	t_env_elem	tmp;

	tmp.value = e->value;
	tmp.key = e->key;
	e->value = n->value;
	e->key = n->key;
	n->value = tmp.value;
	n->key = tmp.key;
	return (cpy);
}

t_env_list	*bubble_sort(t_env_list *cpy)
{
	t_env_elem	*e;
	t_env_elem	*n;

	e = cpy->first;
	n = e->next;
	while (e && n)
	{
		if (ft_strcmp(e->key, n->key) > 0)
		{
			bubble_swap_key(e, n, cpy);
			e = cpy->first;
			n = e->next;
			continue ;
		}
		e = e->next;
		n = e->next;
	}
	return (cpy);
}
