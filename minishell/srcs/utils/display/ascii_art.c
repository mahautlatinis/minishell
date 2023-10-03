/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ascii_art.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malatini <malatini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 21:46:30 by malatini          #+#    #+#             */
/*   Updated: 2021/09/26 12:29:56 by malatini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 ** Affiche un joli prompt au debut du programme
*/
void	ascii_art(void)
{
	ft_putstr_fd("\033[1;36m        _       _     _          _ _ \n", 1);
	ft_putstr_fd("  /\\/\\ (_)_ __ (_)___| |__   ___| | |\n", 1);
	ft_putstr_fd(" /    \\| | '_ \\| / __| '_ \\ / _ \\ | |\n", 1);
	ft_putstr_fd("/ /\\/\\ \\ | | | | \\__ \\ | | |  __/ | |\n", 1);
	ft_putstr_fd("\\/    \\/_|_| |_|_|___/_| |_|\\___|_|_|\033[0m\n\n\n", 1);
}

/**
 * ! Remettre les printf pour faire marcher
** Permet d'afficher les elements de la liste chainee de commande ainsi
** que leurs files associes (suppression de lignes pour la norme)
*** @author malatini
*/
void	display_cmds(t_cmd *cmd)
{
	t_cmd_elem	*elem;
	int			i;
	int			k;

	i = 0;
	k = 0;
	elem = cmd->first;
	while (elem)
	{
		i = 0;
		while (elem->args && elem->args[i])
		{
			i++;
		}
		k++;
		elem = elem->next;
	}
}

/**
 * ! Remettre les printf pour faire marcher
 */
void	print_cmd(t_cmd_elem *elem)
{
	int			i;
	int			j;
	t_file_elem	*file_elem;

	i = 0;
	if (elem)
	{
		while (elem->args && elem->args[i])
			ft_putstr_fd(elem->args[i++], 1);
		j = 0;
		if (elem->file->first)
		{
			file_elem = elem->file->first;
			while (file_elem)
			{
				file_elem = file_elem->next;
				j++;
			}
		}
	}
}

/**
 * ! Remettre les printf pour faire marcher
 */
void	print_args(t_cmd_elem *elem)
{
	int	i;

	i = 0;
	while (elem->args[i])
	{
		i++;
	}
}

/**
 * ! Remettre les printf pour faire marcher
 */
int	print_env(t_mem *mem)
{
	t_env_elem	*tmp;

	tmp = mem->env_list->first;
	while (tmp)
	{
		tmp = tmp->next;
	}
	return (0);
}
