/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahautlatinis <mahautlatinis@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 14:42:05 by malatini          #+#    #+#             */
/*   Updated: 2023/10/13 15:32:05 by mahautlatin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

bool	check_key(char *str, t_mem *mem)
{
	int		i;

	i = 0;
	if (!str[i] || (!ft_isalpha(str[i]) && str[i] != '_'))
	{
		d5_err_p_ret("\': not a valid identifier\n", str, mem, 1);
		return (false);
	}
	i++;
	if (str[i] == '+' || str[i] == '=')
	{
		d5_err_p_ret("\': not a valid identifier\n", str, mem, 1);
		return (false);
	}
	while (str[i] && str[i] != '+' && str[i] != '=')
	{
		if (!(ft_isalnum(str[i]) || str[i] == '_'))
		{
			fprintf(stderr, "%c\n", str[i]);
			d5_err_p_ret("\': not a valid identifier\n", str, mem, 1);
			return (false);
		}
		i++;
	}
	return (true);
}

bool	check_export_key(t_cmd_elem *elem, t_mem *mem)
{
	int	i;

	i = 1;
	while (elem->args[i])
	{
		if (!check_key(elem->args[i], mem))
			return (false);
		i++;
	}
	return (true);
}
