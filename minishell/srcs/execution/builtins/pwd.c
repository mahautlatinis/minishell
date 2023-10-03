/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:46:58 by malatini          #+#    #+#             */
/*   Updated: 2021/09/26 11:11:40 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
** Il nous a ete recommande d utiliser getcwd.
** Car pwd doit marcher meme si l env a ete unset
* @author: malatini
*/
int	ft_exec_pwd(t_mem *mem)
{
	char	*path;

	path = getcwd(NULL, 0);
	ft_putstr_fd(path, 1);
	ft_putstr_fd("\n", 1);
	if (path)
	{
		free(path);
		path = NULL;
	}
	push_ret_elem(mem, 0);
	return (0);
}
