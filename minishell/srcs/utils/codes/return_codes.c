/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   last_return.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahautlatinis <mahautlatinis@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 16:23:51 by malatini          #+#    #+#             */
/*   Updated: 2023/10/13 16:02:41 by mahautlatin      ###   ########.fr       */
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
	return ;
}

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
