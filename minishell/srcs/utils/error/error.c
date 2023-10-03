/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malatini <malatini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 15:58:18 by malatini          #+#    #+#             */
/*   Updated: 2021/09/30 17:21:55 by malatini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
** Fonction d erreur qui peut etre appelee quand le message d erreur
** tiens en une seule chaine de caracteres
* @author: malatini
*/
int	d_err_p_ret(char *error, t_mem *mem, int ret, int fd)
{
	ft_putstr_fd(error, fd);
	push_ret_elem(mem, ret);
	return (ret);
}

int	d2_err_p_ret(char *error, char *arg, t_mem *mem, int ret)
{
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(error, 2);
	push_ret_elem(mem, ret);
	if (!ft_strcmp(error, ": command not found\n"))
		mem->cmd_not_found = false;
	return (ret);
}

int	d3_err(char *error, char *arg, t_mem *mem, int ret)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(error, 2);
	push_ret_elem(mem, ret);
	return (ret);
}

int	d4_err_p_ret(char *error, char *arg, t_mem *mem, int ret)
{
	ft_putstr_fd("bash: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(error, 2);
	push_ret_elem(mem, ret);
	return (ret);
}

int	d5_err_p_ret(char *error, char *arg, t_mem *mem, int ret)
{
	ft_putstr_fd("bash: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(error, 2);
	push_ret_elem(mem, ret);
	return (ret);
}
