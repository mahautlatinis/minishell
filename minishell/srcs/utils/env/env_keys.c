/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahautlatinis <mahautlatinis@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 18:13:22 by malatini          #+#    #+#             */
/*   Updated: 2023/10/13 16:57:29 by mahautlatin      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

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

char	*isolate_key_from_string(char *str, t_mem *mem)
{
	char	*key;
	int		i;

	key = NULL;
	i = 0;
	while (str[i] && str[i] != '=' && str[i] != '+')
		i++;
	if (!str[i])
		return (ft_strdup(str, mem));
	key = ft_strndup(mem, str, i);
	return (key);
}

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

char	*isolate_value_from_string(char *str, t_mem *mem)
{
	char	*value;
	int		i;
	int		j;

	i = 0;
	value = NULL;
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
