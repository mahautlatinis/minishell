/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:47:15 by malatini          #+#    #+#             */
/*   Updated: 2021/09/26 11:12:33 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
** Permet de supprimer proprement l'element unset de la liste
* @author: malatini
*/
int	remove_from_list(t_env_elem *elem, t_mem *mem)
{
	t_env_elem	*tmp;
	t_env_elem	*tmp2;

	tmp = mem->env_list->first;
	if (tmp == elem)
	{
		if (tmp->key)
			free(tmp->key);
		if (tmp->value)
			free(tmp->value);
		tmp2 = tmp->next;
		free(tmp);
		mem->env_list->first = tmp2;
		return (0);
	}
	while (tmp->next != elem && tmp->next)
		tmp = tmp->next;
	tmp->next = elem->next;
	if (elem->key)
		free(elem->key);
	if (elem->value)
		free(elem->value);
	free(elem);
	return (0);
}

/**
 ** Fonction principale pour gerer le builtin unset
 * @author: malatini
 */
int	ft_exec_unset(t_cmd_elem *elem, t_mem *mem)
{
	char		*key;
	int			i;
	t_env_elem	*tmp;

	key = NULL;
	i = 1;
	if (elem->args_len >= 2)
	{
		while (i < elem->args_len)
		{
			tmp = find_key_in_env(elem->args[i], mem);
			if (!tmp)
			{
				i++;
				continue ;
			}
			else
				remove_from_list(tmp, mem);
			i++;
		}
	}
	push_ret_elem(mem, 0);
	return (0);
}
