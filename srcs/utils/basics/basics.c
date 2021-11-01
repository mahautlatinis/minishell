/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malatini <malatini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/19 12:26:20 by malatini          #+#    #+#             */
/*   Updated: 2021/09/26 12:22:04 by malatini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
 * * Retourne la longueur d'une chaine de caractere (classique)
 *** @author malatini
*/
int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

/**
 ** Compare deux strings et retourne 0 s'il n'y a aucune difference
 *** @author: malatini
*/
int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	return (s1[i] - s2[i]);
}

/**
** Allocates memory for a copy of s1, does the copy and returns a point to it.
*** @author: malatini
*/
char	*ft_strdup(const char *s1, t_mem *mem)
{
	int		i;
	char	*cpy;

	i = 0;
	if (!s1)
		return (NULL);
	while (s1[i])
		i++;
	cpy = (char *)malloc(sizeof(char) * (i + 1));
	if (!(cpy))
		failure(-1, mem);
	i = 0;
	while (s1[i])
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

/**
 * * Petite fonction pour verifier le char est une redir
 * @author: malatini
**/
bool	is_redir(char c)
{
	if (c == '<' || c == '>')
		return (true);
	return (false);
}

void	ft_putstr_fd(char *s, int fd)
{
	int		i;

	i = 0;
	if (s)
	{
		while (s[i])
			write(fd, &s[i++], 1);
	}
}
