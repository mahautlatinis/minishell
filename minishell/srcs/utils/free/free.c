/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malatini <malatini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 12:19:58 by malatini          #+#    #+#             */
/*   Updated: 2021/09/25 22:15:04 by malatini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
** Free tous les elements d'une liste chainee de fichiers
* @author: malatini
*/
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
}

/**
** Je free les elements de la liste a partir du file->first mais je ne
** ne free pas la tete de la liste.
* @author: malatini
*/
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
}

/**
**! Free ma liste chainee de commandes et leurs listes de fichiers associees
* @author: malatini
*/
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
}

/**
**Permet de free n'importe quel tableau de char *.
* @author: malatini
*/
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
}
