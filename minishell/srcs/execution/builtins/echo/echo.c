/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahautlatinis <mahautlatinis@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 15:46:51 by malatini          #+#    #+#             */
/*   Updated: 2023/10/13 15:29:39 by mahautlatin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	echo_args(t_cmd_elem *elem, int i)
{
	int	flag;

	flag = 0;
	if (i > 1)
		flag = 1;
	while (elem->args[i] && i < elem->args_len)
	{
		ft_putstr_fd(elem->args[i], 1);
		if (i + 1 < elem->args_len)
			ft_putstr_fd(" ", 1);
		else if (i + 1 == elem->args_len && flag)
			return (0);
		else if (i + 1 == elem->args_len && !flag)
		{
			ft_putstr_fd("\n", 1);
			return (0);
		}
		i++;
	}
	return (0);
}

bool	option(char *a)
{
	if (*a != '-')
		return (false);
	a++;
	if (!*a)
		return (false);
	while (*a)
	{
		if (*a != 'n')
			return (false);
		a++;
	}
	return (true);
}

int	ft_exec_echo(t_cmd_elem *elem, t_mem *mem)
{
	int	i;

	if (elem->args_len < 2)
	{
		ft_putstr_fd("\n", 1);
		push_ret_elem(mem, 0);
		return (0);
	}
	i = 1;
	while (i < elem->args_len && option(elem->args[i]))
		i++;
	if ((echo_args(elem, i)) < 0)
	{
		push_ret_elem(mem, 0);
		return (0);
	}
	return (0);
}
