/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malatini <malatini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 14:34:18 by malatini          #+#    #+#             */
/*   Updated: 2021/09/25 16:19:55 by malatini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
** Permet de free la liste créee pour stocker les variables d'env
*** @author: malatini
*/
void	free_env_list(t_env_list *list)
{
	t_env_elem	*elem;

	if (!list)
		return ;
	elem = list->first;
	while (elem)
	{
		list->first = list->first->next;
		if (elem->key)
			free(elem->key);
		if (elem->value)
			free(elem->value);
		free(elem);
		elem = NULL;
		elem = list->first;
	}
	free(list);
	list = NULL;
}

/**
** Free les elements non necessaires pour la lecture d'une nouvelle ligne
* @author: malatini
*/
void	free_mem_no_exit(t_mem *mem)
{
	if (mem->cmd)
	{
		free_cmd_no_exit(mem->cmd);
		mem->cmd = NULL;
	}
	if (*(mem->buffer))
		(*mem->buffer) = NULL;
}

/**
 * *Fonction de free pour la structure principale
 *** @author: malatini
*/
void	free_mem(t_mem *mem)
{
	if (mem->line)
	{
		free(mem->line);
		mem->line = NULL;
	}
	if (mem->cmd)
	{
		free_cmd(mem->cmd);
		mem->cmd = NULL;
	}
	if (*(mem->buffer))
	{
		free((*(mem->buffer)));
		(*mem->buffer) = NULL;
	}
	if (mem->buffer)
		mem->buffer = NULL;
	if (mem->env_list)
		free_env_list(mem->env_list);
	if (mem->ret_list)
		free_ret_list(mem);
	if (mem)
		free(mem);
}
