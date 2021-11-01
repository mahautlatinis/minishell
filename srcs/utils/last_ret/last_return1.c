/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_return1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 16:34:01 by malatini          #+#    #+#             */
/*   Updated: 2021/09/26 15:53:00 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
** Outils de debug, remettre les printf
* @author: malatini
*/
void	print_ret_list(t_mem *mem)
{
	t_ret_elem	*elem;

	elem = mem->ret_list->first;
	while (elem)
	{
		elem = elem->next;
	}
}

/**
** Renvoie le dernier retour
* @author: malatini
*/
int	return_last_ret(t_mem *mem)
{
	 t_ret_elem	*elem;

	elem = mem->ret_list->first;
	if (!elem)
		return (0);
	while (elem->next)
		elem = elem->next;
	if (elem->ret_code)
		return (elem->ret_code);
	return (0);
}

/**
** Ajoute un element a la liste de retours
* @author: malatini
*/
void	push_ret_elem(t_mem *mem, int ret_value)
{
	t_ret_elem	*elem;
	t_ret_elem	*tmp;

	tmp = NULL;
	(void)mem;
	elem = (t_ret_elem *)malloc(sizeof(t_ret_elem));
	if (!(elem))
		failure(EXIT_FAILURE, mem);
	elem->ret_code = ret_value;
	elem->next = NULL;
	if (!mem->ret_list->first)
		mem->ret_list->first = elem;
	else
	{
		tmp = mem->ret_list->first;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = elem;
	}
}
