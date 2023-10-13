/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahautlatinis <mahautlatinis@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 12:19:58 by malatini          #+#    #+#             */
/*   Updated: 2023/10/13 15:46:09 by mahautlatin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	free_file_list(t_file_list *file)
{
	t_file_elem	*elem;
	t_file_elem	*tmp;

	if (!file)
		return ;
	elem = file->first;
	tmp = elem;
	while (tmp)
	{
		tmp = elem->next;
		free(elem->path);
		free(elem);
		elem = tmp;
	}
	if (file->first)
	{
		free(file->first);
		file->first = NULL;
	}
	if (file)
		free(file);
	return ;
}

void	free_file_list_no_exit(t_file_list *file)
{
	t_file_elem	*elem;
	t_file_elem	*tmp;

	if (!file)
		return ;
	elem = file->first;
	tmp = elem;
	while (tmp)
	{
		tmp = elem->next;
		if (elem->path)
		{
			free(elem->path);
			elem->path = NULL;
		}
		if (elem)
		{
			free(elem);
			elem = NULL;
		}
		elem = tmp;
	}
	free(file);
	return ;
}

void	free_cmd_no_exit(t_cmd *cmd)
{
	t_cmd_elem	*elem;
	t_cmd_elem	*tmp;

	elem = cmd->first;
	tmp = elem;
	while (tmp)
	{
		if (elem->file)
			free_file_list_no_exit(elem->file);
		tmp = elem->next;
		free_tab(elem->args);
		if (elem->path != 0)
			free(elem->path);
		free(elem);
		elem = NULL;
		elem = tmp;
	}
	if (cmd)
		free(cmd);
	cmd = NULL;
	return ;
}

void	free_cmd(t_cmd *cmd)
{
	t_cmd_elem	*elem;
	t_cmd_elem	*tmp;

	elem = cmd->first;
	tmp = elem;
	while (tmp)
	{
		if (elem->file)
			free_file_list(elem->file);
		tmp = elem->next;
		if (elem->file)
		{
			free_file_list(elem->file);
		}
		free_tab(elem->args);
		free(elem);
		elem = NULL;
		elem = tmp;
	}
	if (cmd)
		free(cmd);
	cmd = NULL;
	return ;
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab && tab[i])
	{
		free(tab[i]);
		tab[i] = NULL;
		i++;
	}
	if (tab)
		free(tab);
	tab = NULL;
	return ;
}
