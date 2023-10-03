/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malatini <malatini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 15:11:33 by malatini          #+#    #+#             */
/*   Updated: 2021/09/30 20:06:20 by malatini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
** Permet de savoir la longueur de la liste chainee des variables d'env
* @author: malatini
*/
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

/**
** Fait une copie de la liste chainee des variables d'env pour la trier
* @author: malatini
*/
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

/**
** Fait le swap pour le tri de la copie de la liste chainee d'env
* @author: malatini
*/
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

/**
** Trie alphabetiquement de maniere croissante
* @author: malatini
*/
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
