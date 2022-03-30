/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahautlatinis <mahautlatinis@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 18:13:22 by malatini          #+#    #+#             */
/*   Updated: 2022/03/30 19:01:42 by mahautlatin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/**
* ! Deprecated
* @author: malatini
*/
void	invalid_name_message(char *key)
{
	ft_putstr_fd("export: not a valid identifier", 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(key, 2);
	ft_putstr_fd("\n", 2);
}

char	*ft_strndup(t_mem *mem, char *str, int i)
{
	char	*new;
	int		j;

	new = NULL;
	j = 0;
	new = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!new)
		failure(EXIT_FAILURE, mem);
	while (j < i)
	{
		new[j] = str[j];
		j++;
	}
	new[j] = '\0';
	return (new);
}

/**
** Permet de récupérer la clé quand on a une chaine key=valeur
** revoir si il n y a pas une fonction autorisee qui permet ca
* @author: malatini
*/
char	*isolate_key_from_string(char *str, t_mem *mem)
{
	char	*key;
	int		i;

	(void)mem;
	key = NULL;
	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	if (!str[i])
		return (ft_strdup(str, mem));
	key = ft_strndup(mem, str, i);
	return (key);
}

/**
 * ! Deprecated
** Semblable a un strndup mais le malloc a ete fait avant
* @author: malatini
*/
char	*sub_isolate(char *str, char *value, int i)
{
	int	k;

	k = 0;
	while (str[i])
	{
		value[k] = str[i];
		k++;
		i++;
	}
	value[k] = '\0';
	return (value);
}

/**
** Dans la chaine key=value, isole la key
* @author: malatini
*/
char	*isolate_value_from_string(char *str, t_mem *mem)
{
	char	*value;
	int		i;
	int		j;

	i = 0;
	value = NULL;
	(void)mem;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i])
	{
		i++;
		j = i;
		while (str[i])
			i++;
		value = (char *)malloc(sizeof(char) * (i - j + 1));
		if (!value)
			failure(EXIT_FAILURE, mem);
		i = j;
		value = sub_isolate(str, value, i);
	}
	return (value);
}
