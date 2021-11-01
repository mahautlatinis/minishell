/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_return.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 16:23:51 by malatini          #+#    #+#             */
/*   Updated: 2021/09/26 15:10:02 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	is_last_return(char *str)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(str);
	if (!str)
		return (false);
	if (len != 2)
		return (false);
	if (str[i] && str[i] == '$' && str[i + 1] && str[i + 1] == '?'
		&& !str[i + 2])
		return (true);
	return (false);
}

void	replace_with_last_return(char **str, t_mem *mem)
{
	int	last_ret;

	last_ret = return_last_ret(mem);
	if (is_last_return(*str))
	{
		free(*str);
		*str = NULL;
		*str = ft_itoa(last_ret, mem);
	}
}

/**
* ! Deprecated ?
* @author: malatini
*/
void	loop_for_last_return(t_mem *mem)
{
	t_cmd_elem	*elem;
	t_file_elem	*file_elem;
	int			i;

	elem = mem->cmd->first;
	while (elem)
	{
		i = 0;
		if (elem->args)
		{
			while (elem->args[i])
				replace_with_last_return(&elem->args[i++], mem);
		}
		if (elem->file->first)
		{
			file_elem = elem->file->first;
			while (file_elem)
			{
				replace_with_last_return(&file_elem->path, mem);
				file_elem = file_elem->next;
			}
		}
		elem = elem->next;
	}
}

/**
** Free la liste chainee de retours
* @author: malatini
*/
void	free_ret_list(t_mem *mem)
{
	t_ret_elem	*ret_elem;

	if (!mem->ret_list)
		return ;
	ret_elem = mem->ret_list->first;
	while (ret_elem)
	{
		mem->ret_list->first = mem->ret_list->first->next;
		if (ret_elem)
		{
			free(ret_elem);
			ret_elem = NULL;
		}
		ret_elem = mem->ret_list->first;
	}
	if (mem->ret_list)
	{
		free(mem->ret_list);
		mem->ret_list = NULL;
	}
}

/**
** Fonction principale qui permet de gerer le $?
* @author: malatini
*/
t_ret_list	*init_ret_list(t_mem *mem)
{
	t_ret_list	*ret_list;

	ret_list = (t_ret_list *)malloc(sizeof(t_ret_list));
	if (!(ret_list))
		exit (EXIT_FAILURE);
	ret_list->first = NULL;
	mem->ret_list = ret_list;
	return (ret_list);
}
